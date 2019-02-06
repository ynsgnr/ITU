%clean workspace
%everything created automaticly expect given data in homework (data_logistic.mat)
clear;

%Load data
load('data_logistic.mat');

plot(z(2:91,1),z(2:91,2),'+r');
hold on
plot(z(92:180,1),z(92:180,2),'+b');
plot(z(1,1),z(1,2),'+b');

syms x1 x2 w0 w1 w2 s;
f(x1,x2,w0,w1,w2)=w0+x1*w1+x2*w2; %decision boundry
k(w0,w1,w2,x1)=-(w0/w2)-(w1/w2)*x1; %where g(f(x1,x2)=1/2 (Decision Boundary)

%Iterate w matrix with gradient and sigmaid function
g(s)=1/(1+exp(-s)); %sigmaid function

x=ones(180,3);
for i=1:180
    x(i,2)=z(i,1);
    x(i,3)=z(i,2);
end
n=0.01; %Convergence rate

w=((rand(1,3)-0.5)/50);
graph(x1)=k(w(1),w(2),w(3),x1);
deltaW=ones(1,3)+1;
sw=0; %used as a switch for plotting

while max(abs(deltaW))>1.5
    deltaW=zeros(1,3);
    for i=1:180
        yhat=0;
        for j=1:3
            yhat=yhat+w(j)*x(i,j);
        end
        y=g(yhat);
        for j=1:3
            deltaW(j)=deltaW(j)+(z(i,3)-y)*x(i,j);
        end
    end
    for j=1:3
        w(j)=w(j)+n*deltaW(j);
    end
    %draw graph
    graph(x1)=k(w(1),w(2),w(3),x1);
    if sw==0
        fplot(graph,[0,0.1],'--r');
        sw=1;
    elseif sw==1
        fplot(graph,[0,0.1],'r');
        sw=2;
    elseif sw==2
        fplot(graph,[0,0.1],'--b');
        sw=3;
    elseif sw==3
        fplot(graph,[0,0.1],'b');
        sw=4;
    elseif sw==4
        fplot(graph,[0,0.1],'--g');
        sw=5;
    elseif sw==5
        fplot(graph,[0,0.1],'g');
        sw=0;
    end
    drawnow
end
