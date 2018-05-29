%PCA
%dicrease dimensions of gray_hist
file = fopen('gray_hist.txt','r');
A=fscanf(file,'%d',[16,5613]);
A=A';
[U,S,V]=svd(A);
for r=4:16
    rfile = fopen(['gray_hist_',num2str(r),'dim.txt'],'w+');
    Ar=U(:,1:r)*S(1:r,1:r);
    for i = 1:5613
        for j=1:r
            fprintf(rfile,'%d ',round(Ar(i,j)));
        end
        fprintf(rfile,'\n');
    end
    fclose(rfile);
end
