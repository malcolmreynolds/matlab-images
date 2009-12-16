function hist = alpha_hist(Im,A,transform)
%Histogram of RGB values for an RGB image w/ alpha mask
%Takes an alpha mask which CAN be
%fractional. Im must be uint8! Transform, if present, gives some
%transform that should be done with colorspace.m before doing the conversion.

if (size(Im,3) ~= 3),
  error('alpha_hist:numberOfSamples', 'Input image must be RGB');
elseif (length(size(A)) ~= 2),
  error('alpha_hist:alphaMaskNotAMask','Alpha mask must be 2 dimensional');
elseif (size(A,1) ~= size(Im,1) || size(A,2) ~= size(Im,2)),
  error('alpha_hist:amaskSize','Alpha mask size must match');
elseif max(max(A)) > 1,
  warning('alpha_hist:amaskValuesTooLarge','alpha mask contains values greater than 1!');
end

if isempty(transform),
  transform = 'rgb'; % default, means we don't do a transform
end

numpixels = prod(size(A));

%get our reshaped images and mask, setup bins
A_vec = reshape(A,1,numpixels);
 
%here we setup each line. each struct contains a label identifying
%what the line signifies, then the x range, then the y range (ie
%the bins.
switch transform
 case 'rgb'
  hist.lines{1} = {'r', 0:255, zeros(1,256),0};
  hist.lines{2} = {'g', 0:255, zeros(1,256),0};
  hist.lines{3} = {'b', 0:255, zeros(1,256),0};
  hist.meta = 'rgb histogram'; 
 case 'RGB->lab'
  Im = colorspace(transform,Im);
  hist.lines{1} = {'l',  0:100,zeros(1,101),1};
  hist.lines{2} = {'a^*',-100:1:100,zeros(1,201),101};
  hist.lines{3} = {'b^*',-100:1:100,zeros(1,201),101};
  hist.meta = 'CIE 1976 (L^*, a^*, b^*) histogram';
 otherwise
  error('unsupported transform %s',transform);
end

%put each channel into a long vector, convert to doubles and round
im_chan_1 = round(double(reshape(Im(:,:,1),1,numpixels)));
im_chan_2 = round(double(reshape(Im(:,:,2),1,numpixels)));
im_chan_3 = round(double(reshape(Im(:,:,3),1,numpixels)));
hl1 = hist.lines{1};
hl2 = hist.lines{2};
hl3 = hist.lines{3};

%for the colour ranges which go negative, we need to cope with this
offsets = [hl1{4}, hl2{4}, hl3{4}];
for p=1:numpixels,
  
  amt = A_vec(p);
  
  %yeah, who needs the += operator when we have this kind of
  %fearful conciseness going on.
  hl1{3}(im_chan_1(p)+offsets(1)) = ...
      hl1{3}(im_chan_1(p)+offsets(1)) + amt;
  hl2{3}(im_chan_2(p)+offsets(2)) = ...
      hl2{3}(im_chan_2(p)+offsets(2)) + amt;
  hl3{3}(im_chan_3(p)+offsets(3)) = ...
      hl3{3}(im_chan_3(p)+offsets(3)) + amt;
end

total_alpha = sum(A_vec);

%normalise by number of pixels
hl1{3} = hl1{3} ./ total_alpha;
hl2{3} = hl2{3} ./ total_alpha;
hl3{3} = hl3{3} ./ total_alpha;


