function output = calcTrace (input)
[k,l] = size(input)
if ismatrix(input)& k==4 & l==4
    %check if is the input 4x4 matrix
    output=0;
    for n=1:4
        output=output+input(n,n);
    end
    %sum diagonel entries
else
 error('Plese enter a 4x4 matrix')
end