function h = mask_hist(hist,mask)
% Mask a histogram by zeroing out the parts of the bins using the
% mask. NB - do I renormalise here? maybe?.. I think not for now.
% Thinking about it some more, I think definitely not.

if length(hist.lines) ~= length(mask),
  error('mask_hist:line_count_mismatch',...
        'hist has %d lines, mask has %d lines',...
        length(hist.lines),length(mask));
end

%copy all this to get the metadata etc
h.tag = hist.tag;
h.meta = sprintf('masked(%s)',hist.meta);
h.lines = hist.lines;

for l=1:length(hist.lines),
  h.lines{l}.bins = hist.lines{l}.bins .* mask{l};
  h.lines{l}.lab = sprintf('masked(%s)',hist.lines{l}.lab);
end
 