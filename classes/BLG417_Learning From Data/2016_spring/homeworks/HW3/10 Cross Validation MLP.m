Train = importdata('optdigitstra.mat');%import training data
Test = importdata('optdigitstest.mat');%import test data

F=64; %number of features
I=10; %number of classes
T=3823;%number of data in train
n = 0.002; %learning rate
H = 40; %number of nodes in the hidden layer
B = 25; %number of iterations

Train = Train(randperm(3823),:);%sort training data in random order
accuracyP = zeros(10,1);%Vector that holds the accuracy for each test case 
                        %in 10-fold cross validation
w = zeros(10,H,F+1);%weights of inputs
v = zeros(10,I,H);%weigths of z's(nodes of the hidden layer)
R = zeros(T,10);%Class matrix for training data
z = zeros(H,1);%allocate for nodes of the hidden layers
for i = 1 : T%form the class matrix for the training data
    R(i,Train(i,F+1)+1) = 1;
end
iteration = 0;
for u = 1 : 10%10-fold cross validation, u is for each fold
    %randomize weights w and v
    w(u,:,:) = -0.01 + 0.02 * rand(H,F+1);
    v(u,:,:) = -0.01 + 0.02 * rand(I,H);
    %allocate for deltaV and deltaW
    deltaV = zeros(10,I,H);
    deltaW = zeros(10,H,F+1);
    %form train set and test set for each fold  according to u
    %These train and test sets formed according to the main training data 
    %size. Numbers are specific for this training date case.
    if u == 1
        ROW = 3438;
        train = Train(1:3438,1:F);%train for cross validation
        validate = Train(3439:3823,1:F);%test for cross validation
        r = R(1:3438,:);%Class matrix of train for cross validation
        rV = R(3439:3823,:);%Class matrix of test for cross validation
        cV = Train(3439:3823,F+1);%Classes of test for cross validation
    else
        ROW = 3441;
        s = 3823 - 385;
        s = s - (u-1) * 382;
        train(1:s,:) = Train(1:s,1:F);%train for cross validation
        train(s+1:3441,:) = Train(s+383:3823,1:F);%train for cross validation
        validate = Train(s+1:s+382,1:F);%test for cross validation
        r(1:s,:) = R(1:s,:);%Class matrix of train for cross validation
        r(s+1:3441,:) = R(s+383:3823,:);%Class matrix of train for cross validation
        rV = R(s+1:s+383,:);%Class matrix of test for cross validation
        cV = Train(s+1:s+382,F+1);%Classes of test for cross validation
    end            
for b = 1 : B%back-propagate for each fold
    iteration = iteration + 1;    
    for row = 1 : ROW
        z(1) = 1;
        for h = 2 : H
            o = w(u,h,1) * 1;
            for i = 2 : 65
                o = o + w(u,h,i)*train(row,i-1);
            end     
            z(h) = 1/(1 + exp(-o));
        end
        for i = 1 : I
            y(i) = v(u,i,1);
            for h = 2 : H
                y(i) = y(i) + v(u,i,h) * z(h);
            end
        end
        for i = 1 : I
            deltaV(u,i,:) = n*(r(row,i)-y(i))*z;
        end
        for h = 1 : H
            t = 0;
            for i = 1 : I
                t = t + (r(row,i)-y(i))*v(u,i,h);
            end
            deltaW(u,h,1) = n*t*z(h)*(1-z(h))*1;
            deltaW(u,h,2:65) = n*t*z(h)*(1-z(h))*train(row,:);
        end
        for i = 1 : I
            v(u,i,:) = v(u,i,:) + deltaV(u,i,:);
        end
        for h = 1 : H
            w(u,h,:) = w(u,h,:) + deltaW(u,h,:);
        end
    end
end
%Test accuracy of classification for each test set set aside
%for 10-fold cross validation. Save the results.
accuracy = 0;
    if u == 1
        size = 385;
    else
        size = 382;
    end
    for row = 1 : size
        z(1) = 1;
        for h = 2 : H
            o = w(u,h,1) * 1;
            for i = 2 : F+1
                o = o + w(u,h,i)*validate(row,i-1);
            end     
            z(h) = 1/(1 + exp(-o));
        end
        V = zeros(I,H);
        V(:,:) = v(u,:,:);
        Y(row,:) = V * z;
    end
    [M,Class] = max(Y,[],2);
    Class = Class - 1;
    for i = 1 : size
        if Class(i) == cV(i)
            accuracy = accuracy + 1;
        end
    end
    accuracyP(u) = accuracy * 100 / size;
end
[M,u] = max(accuracyP);%Choose the case(u) which gives the most accurate
                       %classification
%Test the performance of this neural network(MLP) classification
%on the main test set
for row = 1 : 1797
    z(1) = 1;
    for h = 2 : H
        o = w(u,h,1) * 1;
        for i = 2 : F+1
            o = o + w(u,h,i)*Test(row,i-1);
        end     
        z(h) = 1/(1 + exp(-o));
    end
    V = zeros(I,H);
    V(:,:) = v(u,:,:);
    Y(row,:) = V * z;
end
[M,Class] = max(Y,[],2);
Class = Class - 1;
accuracy = 0;
%Calculate the accuracy for the main test set
for i = 1 : 1797
    if Class(i) == Test(i,F+1)
        accuracy = accuracy + 1;
    end
end
accuracyPTest = accuracy * 100 / 1797;
%Accuracy percentages of classification results for each fold in 
%10-fold cross validation
accuracyP
%Accuracy percentage of classification result of the main test set
%Neural network(MLP) is performed according to the fold(u) which 
%gives the highest accuracy
validationAccuracy = sum(accuracyP)/10;%average accuracy of 
                                                %10-fold cross validation
validationAccuracy
accuracyPTest

%Plot the results for the first 20 test data
figure
for i = 1 : 20
    if Class(i) == Test(i,F+1)
        p1 = plot(i,Class(i), 'b*');
        hold on;
    else
        p2 = plot(i,Class(i), 'r*');
        hold on;
        p3 = plot(i,Test(i,F+1), 'g*');
        hold on;
    end
end
xlabel('data number'); % x-axis label
ylabel('classification');
legend([p1 p2 p3],'Right class, right classification','Wrong class, wrong classification', 'Right class, wrong classification');

%Plot the results for the whole test data
figure
for i = 1 : 1797
    if Class(i) == Test(i,F+1)
        p1 = plot(i,Class(i), 'b*');
        hold on;
    else
        p2 = plot(i,Class(i), 'r*');
        hold on;
        p3 = plot(i,Test(i,F+1), 'g*');
        hold on;
    end
end
xlabel('data number'); % x-axis label
ylabel('classification');
legend([p1 p2 p3],'Right class, right classification','Wrong class, wrong classification', 'Right class, wrong classification');