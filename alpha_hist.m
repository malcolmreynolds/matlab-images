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
for col=1:3,
  Im_vec = double(reshape(Im(:,:,col),1,numpixels));
  scaled_im = Im_vec .* A_vec;
  bins{col} = zeros(1,256);
  %optimise this!
  for p=1:numpixels,
    bins{col}(Im_vec(p)+1) = bins{col}(Im_vec(p)+1) + A_vec(p);
  end
end



