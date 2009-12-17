function diff = hist_diff(foo,bar)
%subtracts two colour histograms so the difference can be plotted
%(using draw3hist.m)

%first check both histograms have same type - otherwise we could be
%doing something which doesn't make sense
if ~strcmp(foo.tag,bar.tag),
  msg = sprintf('Histogram types mistmatch, %s and %s',...
                foo.tag, bar.tag);
  warning('hist_diff:different_hist_types',msg);
end
if length(foo.lines) ~= length(bar.lines),
  msg = sprintf('one histogram has %d lines, one has %d!', ...
                length(foo.lines),length(bar.lines));
  error('hist_diff:hist_line_count_mismatch',msg);
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
  msg = sprintf(['lines appear to be about different variables: %s ' ...
                 'and %s'],l1.lab,l2.lab);
  warning('hist_diff:line_labels_differ',msg);
end
if ~isequal(l1.x,l2.x),
  warning('hist_diff:line_xranges_differ','lines have different x ranges');
end
if l1.offs ~= l2.offs,
  msg = sprintf('lines have different offsets: %d and %d',...
                l1.offs,l2.offs);
  warning('hist_diff:line_offs_differ',msg);
end
if length(l1.offs) ~= length(l2.offs),
  msg = sprintf('lines have different bin amounts: %d and %d',...
                length(l1.offs), length(l2.offs));
  warning(msg);
end

l.lab = [l1.lab 'diff'];
l.offs = l1.offs;
l.x = l1.x;
l.bins = double(l1.bins) - double(l2.bins);

end
