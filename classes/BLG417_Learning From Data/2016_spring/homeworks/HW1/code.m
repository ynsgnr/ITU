%clean workspace
%everything created automaticly expect given data in homework (hw1.mat)
clear;

%Load d matrix
load('hw1.mat');

%First class' data:
d1=d(1:1000,:);

%Second class' data:
d2=d(1001:2000,:);

%Randomly selected data:
example=[];

%Traning data:
train=[];

j=0; k=0;

%Select approximately 300 elements from class 1 randomly
for i=1:1000
    if(rand()<0.3)
        j=j+1;
        example(j,1)=d1(i,1); %data1
        example(j,2)=d1(i,2); %data2
        example(j,3)=-1; %Given class
        example(j,4)=0; %KNN2 Prediction
        example(j,5)=0; %KNN5 Prediction
    else
        k=k+1;
        training(k,1)=d1(i,1); %data1
        training(k,2)=d1(i,2); %data2
        training(k,3)=-1;%Given Class:
    end
end

%Select approximately 300 elements from class 2 randomly
for i=1:1000
    if(rand()<0.3)
        j=j+1;
        example(j,1)=d2(i,1); %data1
        example(j,2)=d2(i,2); %data2
        example(j,3)=1; %Given class
        example(j,4)=0; %KNN2 Prediction
        example(j,5)=0; %KNN5 Prediction
    else
        k=k+1;
        training(k,1)=d2(i,1); %data1
        training(k,2)=d2(i,2); %data2
        training(k,3)=1;%Given Class:
    end
end

distances=zeros(j,k,2);

%Calculate Euclidean distance
for i=1:j
    for l=1:k
        distances(i,l,1)=norm([example(i,1),example(i,2)]-[training(l,1),training(l,2)]);
        distances(i,l,2)=training(l,3);
    end
end

sortedDistances=zeros(j,k,2);

%Sort
for i=1:j
    [Y,I]=sort(distances(i,:,1));
    sortedDistances(i,:,:)=distances(i,I,:);
end

index1=0;
index2=0;
sum=0;
%KNN2
for i=1:j
    sum=0;
    for l=1:2
        sum=sum+sortedDistances(i,l,2);
    end
    if(sum<0)
       index1=index1+1;
       example(i,4)=-1;
       KNN2Result1(index1,1)=example(i,1);
       KNN2Result1(index1,2)=example(i,2);
    else
       index2=index2+1;
       example(i,4)=1;
       KNN2Result2(index2,1)=example(i,1);
       KNN2Result2(index2,2)=example(i,2);
    end
end

knn2percentage=0;

for i=1:j
    if(example(i,4)==example(i,3))
        knn2percentage=knn2percentage+1;
    end
end

knn2percentage=knn2percentage/j;

index1=0;
index2=0;

%KNN5
for i=1:j
    sum=0;
    for l=1:5
        sum=sum+sortedDistances(i,l,2);
    end
    if(sum<0)
        index1=index1+1;
        example(i,5)=-1;
        KNN5Result1(index1,1)=example(i,1);
        KNN5Result1(index1,2)=example(i,2);
    else
        index2=index2+1;
        example(i,5)=1;
        KNN5Result2(index2,1)=example(i,1);
        KNN5Result2(index2,2)=example(i,2);
    end
end

knn5percentage=0;

for i=1:j
    if(example(i,5)==example(i,3))
        knn5percentage=knn5percentage+1;
    end
end

index1=0;
index2=0;

for i=1:j
    if(example(i,3)<0)
        index1=index1+1;
        example1(index1,1)=example(i,1);
        example1(index1,2)=example(i,2);
    else
        index2=index2+1;
        example2(index2,1)=example(i,1);
        example2(index2,2)=example(i,2);
    end
end

knn5percentage=knn5percentage/j;

%plot example data
plot(example1(:,1),example1(:,2),'+r');
hold on
plot(example2(:,1),example2(:,2),'+b');

%plot KNN2
plot(KNN2Result1(:,1),KNN2Result1(:,2),'or');
plot(KNN2Result2(:,1),KNN2Result2(:,2),'ob');

%plot KNN5
plot(KNN5Result1(:,1),KNN5Result1(:,2),'dr');
plot(KNN5Result2(:,1),KNN5Result2(:,2),'db');

knn2percentage
knn5percentage
