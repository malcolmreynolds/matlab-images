function result = synth_jar_jar(ims,best)
% to see how good the alpha mask is, synthesise the ball on top of
% jar jar

[jj blah jjmask] = aimread('jar-jar.png');
jj = imresize(jj,[0.5*size(jj,1) NaN]);
jjmask = imresize(jjmask,[0.5*size(jjmask,1),NaN]);
jjmask(jjmask > 1) = 1;

offx = best(4);
offy = best(5);

imwithjarjar = composite(ims.full_target,jj,jjmask,offx,offy);

%we get the alpha mask here but it needs padding with offy rows of
%zeros above and offx columns of zeros on the left
[ignore inferred_mask] = image_from_particle_polar(best,ims.full_bg,...
                                                  ims.full_fg, ...
                                                  ims.full_fgmask);

%pad on left and above
inferred_mask = [zeros(offy,size(inferred_mask,2));...
                 inferred_mask];
inferred_mask = [zeros(size(inferred_mask,1),offx),...
                 inferred_mask];

%now pad on right and bottom
[sy sx] = size(inferred_mask);
[fy fx fblah] = size(ims.full_bg);
inferred_mask = [inferred_mask;...
                 zeros(fy-sy,sx)];
mask = [inferred_mask, ...
        zeros(fy,fx-sx)];
mask = repmat(mask,[1 1 3]);
inv_mask = (1-mask);
                 
%hopefully now it's the right size, so we are going to get the
%pixels in from the original picture (containing the real
%basketball) using the mask and put that on top of the image with
%jar jar
result = (double(imwithjarjar) .* inv_mask) +  ...
         (double(ims.full_target) .* mask);
result = uint8(result);
                

                 