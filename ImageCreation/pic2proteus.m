%PIC2SIM(filename,rows,cols)
%Supports JPEG, GIF, TIFF, PNG
%filename: A string containing the filename (with extension) to be
%converted
%Rows,Cols are effectively the number of row pixels and col pixels that the
%image will be scaled to, to display on the Proteus.  Max size is 320 cols
%and 240 rows. 
%Function will write a new file with name[filename(noextension),'FEH.pic']
function [] = pic2proteus(filename,rows,cols)

if(rows>320 | cols>240)
    fprintf('Max Proteus size is 320x240\n\n');
    return; 
end

if(exist(filename)==0)
    fprintf('FILE DOES NOT EXIST\n\n');
    return;
end


[orig_pic,map,trans]=imread(filename);
scale_pic = imresize(orig_pic,[cols,rows]);
if(~isempty(trans))
    scale_trans = imresize(trans,[cols,rows]);
else
    scale_trans = ones(cols,rows);
end

picsize=size(scale_pic);

filenoext=split(filename,'.');%delimite filename by extension
fehfile=fopen([filenoext{1},'FEH.pic'],'w');
fprintf(fehfile,'%d %d\n',picsize(1),picsize(2));
for(i=1:picsize(1))
    for(j=1:picsize(2))
        if(scale_trans(i,j)~=0)
            color=uint64(scale_pic(i,j,1))*16^4+...
                uint64(scale_pic(i,j,2))*16^2+uint64(scale_pic(i,j,3));
        else
            color=-1;
        end
        fprintf(fehfile,'%d\n',color);
    end
end

fclose(fehfile);

end