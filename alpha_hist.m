function bins = alpha_hist(Im,A)
%alpha_im_hist Histogram of RGB values for an RGB image with
%associated alpha mask. Takes an alpha mask which CAN be
%fractional. Image must be uint8!

if (size(Im,3) ~= 3),
  error('alpha_im_hist:numberOfSamples', 'Input image must be RGB');
elseif (length(size(A)) ~= 2),
  error('alpha_im_hist:alphaMaskNotAMask','Alpha mask must be 2 dimensional');
elseif (size(A,1) ~= size(Im,1) || size(A,2) ~= size(Im,2)),
  error('alpha_im_hist:amaskSize','Alpha mask size must match');
end

numpixels = prod(size(A));

%get our reshaped images and mask, setup bins
A_vec = reshape(A,1,numpixels);
bins.r = zeros(1,256);
bins.g = zeros(1,256);
bins.b = zeros(1,256);

%red
Im_vec_r = double(reshape(Im(:,:,1),1,numpixels));
Im_vec_g = double(reshape(Im(:,:,2),1,numpixels));
Im_vec_b = double(reshape(Im(:,:,3),1,numpixels));
for p=1:numpixels,
  amt = A_vec(p);
  bins.r(Im_vec_r(p)+1) = bins.r(Im_vec_r(p)+1) + amt;
  bins.g(Im_vec_g(p)+1) = bins.g(Im_vec_g(p)+1) + amt;
  bins.b(Im_vec_b(p)+1) = bins.b(Im_vec_b(p)+1) + amt;
end


