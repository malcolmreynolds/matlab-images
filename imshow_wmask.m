function imshow_wmask(im,mask)
% Same as imshow, but allows a mask of doubles in the range [0 1]
% to be specified as well

imshow(uint8(double(im).*repmat(mask,[1 1 3])));