% %import data and eliminate ids
% train = importdata('Train.mat');
% test = importdata('Test.mat');
% 
% F=93;
% sizeTrain=size(train,1);
% sizeTest=size(test,1);
% 
% ids=test(:,1);
% train=train(:,2:F+2);
% test=test(:,2:F+1);
% 
% knn250=fitcknn(train(:,1:F),train(:,F+1),'NumNeighbors',250);
% knn300=fitcknn(train(:,1:F),train(:,F+1),'NumNeighbors',300);
% knn250train=knn250.predict(train(:,1:F));
% knn300train=knn300.predict(train(:,1:F));
% knn250pred=knn250.predict(test);
% knn300pred=knn300.predict(test);
% knnsTrain=zeros(6,sizeTrain);
% knnsTest=zeros(6,sizeTest);
% for i=1:6
%     %Needed for classifier
%    knnModel= fitcknn(train(:,1:F),train(:,F+1),'NumNeighbors',i*10);
%    knnsTrain(i,:)=knnModel.predict(train(:,1:F));
%    knnsTest(i,:)=knnModel.predict(test);
% end
%Code above here calculated in knns.mat

load('knns.mat');

flatFeatures=train(:,1:93);
%If its bigger than 1 make it 1
for i=1:61878
   for j=1:93
       if flatFeatures(i,j)>1
           flatFeatures(i,j)=1;
       end
   end
end
%prep for neural net
neuralClasses=zeros(61878,9);
for i=1:61878
    neuralClasses(i,train(i,94))=1;
end
%PCA
[V, U] = pca(flatFeatures);
trainRedDimenFlat=U*V';
trainRedDimenFlat15=trainRedDimenFlat(:,1:15);
trainRedDimenFlat30=trainRedDimenFlat(:,1:30);
%training data reduced dimensions from binary features with 15 or 30
trainRedDimenFlat15R=[train(:,1:93),trainRedDimenFlat15];
trainRedDimenFlat30R=[train(:,1:93),trainRedDimenFlat30];

%Two matrices used to train a neural net with 50 and 60 hidden layers
%nnstart trainRedDimenZero15R
%nnstart trainRedDimenZero30R

tPCA15r=NeuralNetworkFeaturePCA15(trainRedDimenFlat15R);
tPCA30r=NeuralNetworkFeaturePCA30(trainRedDimenFlat30R);

combinedTrain=[knn250train,knn300train,transpose(knnsTrain),tPCA15r,tPCA30r];
%to train final neural network
%nnstart combinedTrain

%remapping does not work
%adding features to combinedTrain does not work

%Training completed neural network fonctiouns can be found in the folder
%and data can be found at trainedData.mat

%Classifier Starts here:

flatFeatures=test(:,1:93);
%If its bigger than 1 make it 1
for i=1:sizeTest
   for j=1:F
       if flatFeatures(i,j)>1
           flatFeatures(i,j)=1;
       end
   end
end

%PCA
testRedDimenFlat30=flatFeatures*V(:,1:30);
testRedDimenFlat30=testRedDimenFlat30(:,1:30);
testRedDimenFlat15=flatFeatures*V(:,1:15);
testRedDimenFlat15=testRedDimenFlat15(:,1:15);
testRedDimenFlat15R=[test,testRedDimenFlat15];
testRedDimenFlat30R=[test,testRedDimenFlat30];

fPCA15r=NeuralNetworkFeaturePCA15(testRedDimenFlat15R);
fPCA30r=NeuralNetworkFeaturePCA30(testRedDimenFlat30R);

%Combine all results:
combinedTest=[knn250pred,knn300pred,transpose(knnsTest),fPCA15r,fPCA30r];
results=finalNetwork(combinedTest);

resultsMatrix=results;
for i=1:size(results,1)
    if knnsTest(6,i)>=5
        resultsMatrix(i,knnsTest(6,i))=resultsMatrix(i,knnsTest(6,i))+1;
    elseif knn300pred(i)==2
        resultsMatrix(i,2)=resultsMatrix(i,2)+1;
    end
end

%softmax
resultsMatrix=transpose(softmax(transpose(resultsMatrix)));
resultsMatrix=[ids,resultsMatrix];