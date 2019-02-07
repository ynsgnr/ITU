#BLG 354E 2018 Apr HW-2 Istanbul Technical University
#Yunus Güngör-Student No:150150701
#question 2

import numpy as np

from sklearn.pipeline import Pipeline
from sklearn.decomposition import PCA
from sklearn.linear_model import LogisticRegression as LR
from scipy.io.wavfile import read

#
#Assumed that, 'one' sound files saved under folder './one'
#with numbers as name in wav format.
#
#Assumed that, 'two' sound files saved under folder './two'
#with numbers as name in wav format.
#
#Ex: first sound file for 'one' is './one/1.wav'
#Ex: second sound file for 'two' is './two/2.wav'
#
#First 15 files from each folder used as training
#Last 5 files from each folder used as test
#Choosing test and data files can be randomized but not necassary

#Values used for dataset
numberOfTotalData=40
numberOfTrainingData=30
numberOfTestData=numberOfTotalData-numberOfTrainingData

#Values used for different combinations
maxNumberOfCoefficents=100
minNumberOfCoefficents=10
minComponentsToKeep=1
maxComponentsToKeep=10


trainData = np.zeros(shape=(numberOfTrainingData,maxNumberOfCoefficents))
testData = np.zeros(shape=(numberOfTestData,maxNumberOfCoefficents))
classes= np.zeros((numberOfTrainingData,1))
testClasses= np.zeros((numberOfTestData,1))

for i in range(1,int(numberOfTrainingData/2+1)):
    fs, data = read('./one/'+str(i)+'.wav')
    sound = data.T[0]
    coeff = np.fft.fft(sound)
    coeff=coeff[:int(len(coeff)/2)] #pick half of fft(symetric)
    coeff=coeff[:maxNumberOfCoefficents] #pick first coefficents
    coeff=abs(coeff)#pick amplitude
    trainData[i-1]=coeff
    classes[i-1]=1 #class

for i in range(1,int(numberOfTrainingData/2+1)):
    fs, data = read('./two/'+str(i)+'.wav')
    sound = data.T[0]
    coeff = np.fft.fft(sound)
    coeff=coeff[:int(len(coeff)/2)] #pick half of fft(symetric)
    coeff=coeff[:maxNumberOfCoefficents] #pick first coefficents
    coeff=abs(coeff)#pick amplitude
    trainData[int(numberOfTrainingData/2-1)+i]=coeff
    classes[int(numberOfTrainingData/2-1)+i]=2 #class

for i in range(int(numberOfTrainingData/2+1),int(numberOfTotalData/2+1)):
    fs, data = read('./one/'+str(i)+'.wav')
    sound = data.T[0]
    coeff = np.fft.fft(sound)
    coeff=coeff[:int(len(coeff)/2)] #pick half of fft(symetric)
    coeff=coeff[:maxNumberOfCoefficents] #pick first coefficents
    coeff=abs(coeff)#pick amplitude
    testData[i-int(numberOfTrainingData/2+1)]=coeff
    testClasses[i-int(numberOfTrainingData/2+1)]=1 #class

for i in range(int(numberOfTrainingData/2+1),int(numberOfTotalData/2+1)):
    fs, data = read('./two/'+str(i)+'.wav')
    sound = data.T[0]
    coeff = np.fft.fft(sound)
    coeff=coeff[:int(len(coeff)/2)] #pick half of fft(symetric)
    coeff=coeff[:maxNumberOfCoefficents] #pick first coefficents
    coeff=abs(coeff)#pick amplitude
    testData[i-int(numberOfTestData+1)]=coeff
    testClasses[i-int(numberOfTestData+1)]=2 #class

#Data parsing and fourier transforms have been completed.
#Test each combination of PCA values kept and coefficent values taken
#print the most successfull combination

maxSuccessRate=np.zeros(3)

for i in range(minNumberOfCoefficents,maxNumberOfCoefficents):
    for j in range(minComponentsToKeep,maxComponentsToKeep):
        pipeline=Pipeline(memory=None,steps=[('pca',PCA(n_components=j)),('lr',LR())])

        pipeline.fit(trainData[:,0:i],classes.ravel())
        result = pipeline.predict(testData[:,0:i])

        print('Number of coefficents:'+str(i))
        print('PCA values kept:'+str(j))
        print('Classification results:')
        print(result)
        success=0
        for k in range(0,numberOfTestData):
            if(result[k]==abs(testClasses[k])):
                success=success+1
        successRate=(success/numberOfTestData)
        print('Success rate:')
        print(successRate)
        if(maxSuccessRate[0]<successRate):
            maxSuccessRate[0]=successRate
            maxSuccessRate[1]=i
            maxSuccessRate[2]=j

print('\nDone.')
print('Most Succesfull rate: '+str(maxSuccessRate[0]))
print('When, coefficent number is: '+str(maxSuccessRate[1])+' and PCA values kept is '+str(maxSuccessRate[2]))
