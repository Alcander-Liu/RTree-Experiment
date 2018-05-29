%transform colored pic to gray pic
img = fopen('imagelist.txt','r');
i=1;
while feof(img)==0
    tline = fgetl(img);
    A=imread(tline);
    h=rgb2gray(A);
    imwrite(h,[num2str(i),'.JPEG']);
    i=i+1;
end

%get original gray hist vector
feature = fopen('gray_hist.txt','w');
for i=1:5613
    A=imread([num2str(i),'.JPEG']);
    h=imhist(A,16);
    h=h/M/N;
    h=h*10^5;
    for j=1:16
        fprintf(feature,'%d ',round(h(j)));
    end
    fprintf(feature,'\n');
end
 
