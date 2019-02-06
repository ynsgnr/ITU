Train = importdata('optdigitstra.mat');%import training data
Test = importdata('optdigitstest.mat');%import test data

F=64; %number of features
I=10; %number of classes
T=3823;%number of data in train
n = 0.002; %learning rate
H = 40; %number of nodes in the hidden layer
B = 25; %number of iterations
autoB = 5;


tra1 = Train;

%apply autoencode
    autoH1=20;
    autoH2=2;
    autoH3=20;
    autoZ1= zeros(1,autoH1); %layer 1 - %30 NODES
    autoZ2= zeros(1,autoH2); % layer 2-encoder - 2 NODES
    autoZ3= zeros(1,autoH3); % layer 3 - decoder - 30 NODES
    w1 = -0.001 + 0.002 * rand(autoH1,F+1);
    w2 = -0.001 + 0.002 * rand(autoH2,autoH1+1);
    w3 = -0.001 + 0.002 * rand(autoH3,autoH2);
    deltaW1 = zeros(autoH1,F+1);
    deltaW2 = zeros(autoH2,autoH1+1);
    deltaW3 = zeros(autoH3,autoH2);
    autoV = -0.01 + 0.02 * rand(F,autoH3);
    deltaV = zeros(F,autoH3);
    for b=1:autoB
        for row = 1 : T
            autoZ1(1) = 1; %layer 1 - %30 NODES
            %autoZ2(1) = 1; % layer 2 - encoder - 2 NODES
            autoZ3(1) = 1; % layer 3 - decoder - 30 NODES
            for h = 2 : autoH1
                o1 = w1(h,1) * 1;
                for i = 2 : F+1
                    o1 = o1 + w1(h,i)*tra1(row,i-1);
                end
                autoZ1(h) = 1/(1 + exp(-o1));
            end
            for h = 1 : autoH2
                  o1 = 0;
                  for i = 1 : autoH1
                      o1 = o1 + w2(h,i)*autoZ1(i);
                  end    
                autoZ2(h) = 1/(1 + exp(-o1));
            end
            for h = 2 : autoH3
                o3 = w3(h,1) * 1;
                for i = 1 : autoH2
                    o3 = o3 + w3(h,i)*autoZ2(i);
                end     
                autoZ3(h) = 1/(1 + exp(-o3));
            end
            for i = 1 : F
                y(i) = autoV(i,1);
                for h = 2 : autoH3
                    y(i) = y(i) + autoV(i,h) * autoZ3(h);
                end
            end
            for i = 1 : F
                deltaV(i,:) = n*(tra1(row,i)-y(i))*autoZ3;
            end
            for h = 1 : autoH3
                t = 0;
                for i = 1 : F
                    t = t + (tra1(row,i)-y(i))*autoV(i,h);
                end
                deltaW3(h,1) = n*t*autoZ3(h)*(1-autoZ3(h))*1;
                deltaW3(h,2:autoH2+1) = n*t*autoZ3(h)*(1-autoZ3(h))*autoZ2;
            end
            for h = 1 : autoH2
                t = 0;
                for i = 1 : 20
                    t = t + (tra1(row,i)-y(i))*w3(i,h);
                end
                deltaW2(h,1) = n*t*autoZ2(h)*(1-autoZ2(h))*1;
                deltaW2(h,2:autoH1+1) = n*t*autoZ2(h)*(1-autoZ2(h))*autoZ1;
            end
            for h = 1 : autoH1
                t = 0;
                for i = 1 : 2
                    t = t + (tra1(row,i)-y(i))*w2(i,h);
                end
                deltaW1(h,1) = n*t*autoZ1(h)*(1-autoZ1(h))*1;
                deltaW1(h,2:F+1) = n*t*autoZ1(h)*(1-autoZ1(h))*tra1(row,1:F);
            end
            for i = 1 : F
                autoV(i,:) = autoV(i,:) + deltaV(i,:);
            end
            for h = 1 : autoH1
                w1(h) = w1(h) + deltaW1(h);
            end
            for h = 1 : autoH2
                w2(h) = w2(h) + deltaW2(h);
            end
            for h = 1 : autoH3
                w3(h) = w3(h) + deltaW3(h);
            end
        end
        
for row = 1 : T
            autoZ1(1) = 1;
            for h = 2 : autoH1
                o = w1(h,1) * 1;
                for i = 2 : F+1
                    o = o + w1(h,i)*tra1(row,i-1);
                end
                autoZ1(h) = 1/(1 + exp(-o));
            end
            for h = 1 : autoH2
                for i = 1 : autoH1
                    o = o + w2(h,i)*autoZ1(i);
                end
                autoZ2(h) = 1/(1 + exp(-o));
            end
            autoZ3(1)=1;
            for h = 1 : autoH3
                for i = 1 : autoH2
                    o = o + w3(h,i)*autoZ2(i);
                end
                autoZ3(h) = 1/(1 + exp(-o));
            end
            autoY(row,:) = autoV * transpose(autoZ3);
        end
        
%         error=0;
%         for t=1:T
%             for f=1:F
%              error=error+((tra1(t,f)-autoY(t,f))^2);
%             end
%         end
%         error=sqrt(error);
%         
%         hold on
%         plot(b,error,'+r');
%         drawnow;
        
    end
    
    data=zeros(T,2);
            for row = 1 : T
                autoZ1(1) = 1;
                for h = 2 : autoH1
                    o = w1(h,1) * 1;
                    for i = 2 : F+1
                        o = o + w1(h,i)*tra1(row,i-1);
                    end
                    autoZ1(h) = 1/(1 + exp(-o));
                end
                for h = 1 : autoH2
                    for i = 1 : autoH1
                        o = o + w2(h,i)*autoZ1(i);
                    end
                    autoZ2(h) = 1/(1 + exp(-o));
                end
                data(row,:) = autoZ2;
            end
    F=2;
    
    tra1=[data,tra1(:,F+1)];
    Train = tra1(randperm(T),:);
    tra=tra1(:,1:F);
    
    F = 64;
     data=zeros(1797,2);
    for row = 1 : 1797
                autoZ1(1) = 1;
                for h = 2 : autoH1
                    o = w1(h,1) * 1;
                    for i = 2 : F+1
                        o = o + w1(h,i)*Test(row,i-1);
                    end
                    autoZ1(h) = 1/(1 + exp(-o));
                end
                for h = 1 : autoH2
                    for i = 1 : autoH1
                        o = o + w2(h,i)*autoZ1(i);
                    end
                    autoZ2(h) = 1/(1 + exp(-o));
                end
                data(row,:) = autoZ2;
    end
            F= 2;
     test=[data,Test(:,65)];

  
    
    
    
    
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
            for i = 2 : F+1
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
            deltaW(u,h,2:F+1) = n*t*z(h)*(1-z(h))*train(row,:);
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
            o = o + w(u,h,i)*test(row,i-1);
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
    if Class(i) == test(i,F+1)
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
    if Class(i) == test(i,F+1)
        p1 = plot(i,Class(i), 'b*');
        hold on;
    else
        p2 = plot(i,Class(i), 'r*');
        hold on;
        p3 = plot(i,test(i,F+1), 'g*');
        hold on;
    end
end
xlabel('data number'); % x-axis label
ylabel('classification');
legend([p1 p2 p3],'Right class, right classification','Wrong class, wrong classification', 'Right class, wrong classification');

%Plot the results for the whole test data
figure
for i = 1 : 1797
    if Class(i) == test(i,F+1)
        p1 = plot(i,Class(i), 'b*');
        hold on;
    else
        p2 = plot(i,Class(i), 'r*');
        hold on;
        p3 = plot(i,test(i,F+1), 'g*');
        hold on;
    end
end
xlabel('data number'); % x-axis label
ylabel('classification');
legend([p1 p2 p3],'Right class, right classification','Wrong class, wrong classification', 'Right class, wrong classification');