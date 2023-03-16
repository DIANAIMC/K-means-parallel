getwd()
setwd("C:/Users/52552/Documents/CPYN/cpp/parcial1")

datos <- read.csv("resultados.csv", header = TRUE)
datos

library(ggplot2)
library(forcats)
graf1 <- ggplot(datos,aes(x=as.factor(cores),y=tiempo, fill="blue"))+
  geom_bar(stat = "identity")+
  labs(x = "Nucleos", 
       y = "Tiempo", 
       title = "Rendimiento por hilos",
       subtitle = "",
       fill="Color")
graf1

library(reshape)
melt_df <- melt(datos,id="tamano")
melt_df
graf1 <- datos %>% 
  ggplot(aes(x=tamano, y=tiempo, fill=factor(cores))) +  
  geom_point(shape=21, color="black",size=3)
graf1

library(dplyr)
proms <- group_by(datos, cores, tamano) %>% summarise(average = mean(tiempo))
ggplot(data = proms)+aes(x = tamano, y = average, color = as.factor(cores))+
  geom_line(size=2)+labs(color = "Hilos", x = "Tamaño de muestra", y = "Promedio de tiempo")