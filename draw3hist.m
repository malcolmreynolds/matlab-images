function draw3hist(hist,the_title)

%only support maximum of 4 lines right now
colours = {'r','g','b','k'};

hold on;
labels = cell(0,1);
for l=1:length(hist.lines),
  plot(hist.lines{l}.x,hist.lines{l}.bins,colours{l});
  labels = [labels hist.lines{l}.lab];
end

legend(labels);
title(the_title);
hold off;
