%hsv moment
file = fopen('imagelist.txt','r');
fdata = fopen('hsv_moment.txt','w+');
while feof(file)==0
    tline = fgetl(file);
    img=imread(tline);
    %imshow(img);
    img=rgb2hsv(img);
    H1=img(:,:,1);
    S1=img(:,:,2);
    V1=img(:,:,3);
    vector(1)=mean(H1(:));
    vector(2)=mean(S1(:));
    vector(3)=mean(V1(:));
    %var
    vector(4)=var(H1(:),1);
    vector(5)=var(S1(:),1);
    vector(6)=var(V1(:),1);
    %skew
    H1=(H1-vector(1)).^3;
    S1=(S1-vector(2)).^3;
    V1=(V1-vector(3)).^3;
    vector(7)=mean(H1(:))/((vector(4)^(3/2)));
    vector(8)=mean(S1(:))/((vector(5)^(3/2)));
    vector(9)=mean(V1(:))/((vector(6)^(3/2)));
    %print
    for i=1:9
        fprintf(fdata,'%.6f ',vector(i));
    end
    fprintf(fdata,'\n');
end
