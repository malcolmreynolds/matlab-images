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

if nargin == 2,
  transform = 'rgb'; % default, means we don't do a transform
end

numpixels = prod(size(A))

%get our reshaped images and mask, setup bins
A_vec = reshape(A,1,numpixels);
 
%here we setup each line. each struct contains a label identifying
%what the line signifies, then the x range, then the y range (ie
%the bins.
switch transform
 case 'rgb'
  %use of temporary variable l is really to make things look nice
  %and cleaner.
  l.lab='r'; l.x = 0:255; l.offs = 1;
  hist.lines{1} = l;
  l.lab='g'; l.x = 0:255; l.offs = 1;
  hist.lines{2} = l;
  l.lab='b'; l.x = 0:255; l.offs = 1;
  hist.lines{3} = l;
  hist.meta = 'rgb histogram';
  hist.tag = 'rgb'; %tells the plotting function how to act
 case 'RGB->lab'
  Im = colorspace(transform,Im);
  l.lab='L';   l.x = 0:100; l.offs = 1;
  hist.lines{1} = l;
  l.lab='a^*'; l.x = -100:1:100; l.offs = 101;
  hist.lines{2} = l;
  l.lab='b^*'; l.x = -100:1:100; l.offs = 101;
  hist.lines{3} = l;
  hist.meta = 'CIE 1976 (L^*, a^*, b^*) histogram';
  hist.tag = 'lab';
 otherwise
  error('unsupported transform %s',transform);
end

%if I was calling out to C, I would do it just here
%note the offset passed is for matlab version - subtract 1 once
%inside C!!!

if USING_MEX,
  
  fprintf('using mex\n');

  for c=1:3,
    hist.lines{c}.bins = alpha_hist_1d_mex(sint32(Im(:,:,c)), ...
                                           double(A),...
                                           uint32(hist.lines{c}.offs), ...
                                           uint32(length(hist.lines{c}.x));
  end
  
else %slower matlab version
  
  fprintf('using matlab version\n');
  
  %put each channel into a long vector, convert to doubles and round
  im_chan_1 = round(double(reshape(Im(:,:,1),1,numpixels)));
  im_chan_2 = round(double(reshape(Im(:,:,2),1,numpixels)));
  im_chan_3 = round(double(reshape(Im(:,:,3),1,numpixels)));
  
  
  hl1bin = hist.lines{1}.bins;
  hl2bin = hist.lines{2}.bins;
  hl3bin = hist.lines{3}.bins;
  off1 = hist.lines{1}.offs;
  off2 = hist.lines{2}.offs;
  off3 = hist.lines{3}.offs;
 
  for p=1:numpixels,
    
    amt = A_vec(p);
    
    %yeah, who needs the += operator when we have this kind of
    %fearful conciseness going on.
    hl1bin(im_chan_1(p) + off1) = ...
        hl1bin(im_chan_1(p) + off1) + amt;
    hl2bin(im_chan_2(p) + off2) = ...
        hl2bin(im_chan_2(p) + off2) + amt;
    hl3bin(im_chan_3(p) + off3) = ...
        hl3bin(im_chan_3(p) + off3) + amt;
    %fprintf('pix %d alpha is %f\n',p,amt);
  end
  
  total_alpha = sum(A_vec);
  
  %normalise by number of pixels
  hist.lines{1}.bins = hl1bin ./ total_alpha;
  hist.lines{2}.bins = hl2bin ./ total_alpha;
  hist.lines{3}.bins = hl3bin ./ total_alpha;
  
end
  
  