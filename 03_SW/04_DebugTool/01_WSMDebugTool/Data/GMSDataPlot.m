
fid = fopen('GMSData._carnibalr_b#12.txt', 'r');
buf = fscanf(fid, '%d');
fclose(fid);
buf_x = buf(1:3:end);
buf_y = buf(2:3:end);
buf_z = buf(3:3:end);

figure(1), 
subplot(3, 1, 1), plot(buf_x, 'r'), title('x axis');
subplot(3, 1, 2), plot(buf_y, 'g'), title('y axis');
subplot(3, 1, 3), plot(buf_z, 'b'), title('z axis');

% z = buf_y + i*buf_z;
% 
% 
% theta = angle(z);
% mag = abs(z);
% 
% figure(3),
% polar(theta, mag, '*');
% 
% 
% [xc, yc, radius, mag]= circfit(buf_y, buf_z);
% 
% figure(4), 
% f=@(x, y)((x-xc).^2 + (y-yc).^2 - radius^2);
% ezplot(f, [-6000 6000]);
% 
% xc
% yc
% radius









