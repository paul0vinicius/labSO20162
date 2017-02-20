library(ggplot2)

p<-read.table("data_plot.txt",header=T,sep="|")
str(p)
qplot(data=p,x=N.Of.Processes,y=Runtime.ms,geom="boxplot")
qplot(data=p,x=N.Of.Processes,y=Switches,geom="boxplot")
qplot(data=p,x=N.Of.Processes,y=Average.delay.ms,geom="boxplot")
qplot(data=p,x=N.Of.Processes,y=Time,geom="boxplot")
