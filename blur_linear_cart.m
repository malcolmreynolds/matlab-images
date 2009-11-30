function br = blur_linear_cart(Im,xb,yb)
% Blurs image I in the direction given by (xb,yb).
k = fspecial('motion',sqrt(xb^2 + yb^2),(atan(yb/xb)/pi)*180);
br = imfilter(Im,k,'conv','replicate');
