function br = blur_linear_polar(Im,r,theta)
% Blurs image Im according to polar coords (r,theta)
k = fspecial('motion',r,theta);
br = imfilter(Im,k,'conv','replicate','full');
