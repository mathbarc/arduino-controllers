Kp=0.023404;
Ti = 0.0009;
Ki = (Kp*T)/Ti;
Dpi = Kp + Ki*(1/(z-1));
Tpi = feedback(Dpi*Gmfz,1);
step(Tpi,Gmfz);