function cube = im_hist_cube(Im,A)

if size(Im,3) ~= 3,lim
  error('im_hist_cube:numberOfSamples','Input image must be RGB');
elseif length(size(A)) ~= 2,
  error('im_hist_cube:alphaMaskNotAMask',['Alpha mask must be 2 ' ...
                      'dimensional']);
elseif size(A,1) ~= size(Im,1) || size(A,2) ~= size(Im,2),
  error('im_hist_cube:amaskSize','Alpha mask size must match');
elseif max(max(A)) > 1,
  warning('im_hist_cube:amaskValuesTooLarge',['alpha mask contains ' ...
                      'values greater than 1!']);
end

%create the cube
cube = zeros(256,256,256);

for x = 1:size(Im,2),
  for y = 1:size(Im,1),
    if A(y,x) == 0.0,
      continue;
    end
    %I hate matlab i will kill it
    r = uint16(Im(y,x,1));
    g = uint16(Im(y,x,2));
    b = uint16(Im(y,x,3));
    cube(r+1,g+1,b+1) = cube(r+1,g+1,b+1) + A(y,x);
%    fprintf('p%d: (%d,%d,%d,%f)',...
%            (x-1)*size(Im,1)+(y-1), ...
%            r,g,b,A(y,x));
%    fprintf(' - increment cube(%d,%d,%d) to %f\n', ...
%            r,g,b,cube(r+1,g+1,b+1));
  end
end