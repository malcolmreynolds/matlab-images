function hist = alpha_hist(Im,A,transform)
% parked function. This has now been superceded by alpha_hist which always
% passes through to alpha_hist_mex.c - this is just left as a reference to
% the more principalled but slow and crappy way.

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

numpixels = prod(size(A));

%get our reshaped images and mask, setup bins
A_vec = reshape(A,1,numpixels);
 
%here we setup each line. each struct contains a label identifying
%what the line signifies, then the x range, then the y range (ie
%the bins. Note all the offsets here are setup for matlab ie arrays
%that start at zero. the C function decrements to take care of this.
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

imsint32 = int32(Im);
for c=1:3,
  %we now pass the full image, plus offset and length parameters
  hist.lines{c}.bins = alpha_hist_mex(imsint32,uint32((c-1)*numpixels),...
                                      uint32(numpixels), ...
                                      double(A),...
                                      uint32(hist.lines{c}.offs), ...
                                      uint32(length(hist.lines{c}.x)));
end
  
  
  
