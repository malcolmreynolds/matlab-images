function new_bins = combine_bins(bins,n)
%Consolidate a histogram into a smaller number of bins, n
% n must be an exact divisor of the number of bins provided.

if mod(length(bins),n) ~= 0,
  error('combine_bins:valueOfN', ...
        sprintf('%d doesn''t divide %d',n,length(bins)));
elseif prod(size(bins)) ~= length(bins),
  error('combine_bins:mtxBinsPassed', ...
        'Matrix passed as bins, must provide vector.');
end

num_to_combine = length(bins)/n;
new_bins = sum(reshape(bins,num_to_combine,n));
