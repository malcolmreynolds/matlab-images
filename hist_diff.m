function diff = hist_diff(foo,bar)
%subtracts two colour histograms so the difference can be plotted
%(using draw3hist.m)

%first check both histograms have same type - otherwise we could be
%doing something which doesn't make sense
if ~strcmp(foo.tag,bar.tag),
  warning('hist_diff:different_hist_types',...
          'Histogram types mismatch, %s and %s',...
          foo.tag,bar.tag);
end
if length(foo.lines) ~= length(bar.lines),
  error('hist_diff:hist_line_count_mismatch',...
        'one histogram has %d lines, one has %d!',...
        length(foo.lines),length(foo.lines));
end

diff.tag = foo.tag;
diff.meta = sprintf('difference: %s - %s',foo.tag, bar.tag);

for i=1:length(foo.lines)
  diff.lines{i} = linediff(foo.lines{i},bar.lines{i});
end

end



function l = linediff(l1, l2)
%form a new line to be plotted which is the difference between two
%lines
if ~strcmp(l1.lab,l2.lab),
  warning('hist_diff:line_labels_differ',...
          'lines appear to be about different variables: %s and %s',...
          l1.lab,l2.lab);
end
if ~isequal(l1.x,l2.x),
  warning('hist_diff:line_xranges_differ','lines have different x ranges');
end
if l1.offs ~= l2.offs,
  warning('hist_diff:line_offs_differ',...
          'lines have different offsetes: %d and %d');
end
if length(l1.bins) ~= length(l2.bins), 
  warning('hist_diff:bin_len_differ',...
          'lines have different bin sizes: %d and %d',...
          length(l1.bins),length(l2.bins));
end

l.lab = [l1.lab 'diff'];
l.offs = l1.offs;
l.x = l1.x;
l.bins = double(l1.bins) - double(l2.bins);

end
