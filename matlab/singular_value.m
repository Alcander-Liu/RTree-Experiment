feature = fopen('gray_singular.txt','w');
for i=1:5613
    A=imread([num2str(i),'.JPEG']);
    A=im2double(A);
    [U,S,V]=svd(A);
    h = 1000/S(1,1);
    for j=1:16
        fprintf(feature,'%.4f ',h*S(j,j));
    end
    fprintf(feature,'\n');
end
