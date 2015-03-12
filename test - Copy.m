function [ y ] = test()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
   % Turn image into data matrix
    img = imread('img8.jpg');
    
    %converts image to grayscale
     img = rgb2gray(img);
     
     %number of rows of the matrix
     height = size(img, 1);
     width = size(img, 2);
    
     %algorithm that reduce an image by half.
     inputI = img;
     [r,c] = size(inputI);
     
     %calculate the scale factor
     scaleFactorHeight = r / 28;
     scaleFactorWidth = c /28;
     scale = [1/scaleFactorWidth 1/scaleFactorHeight];       
     %create a 28x28 matrix and initialize with 0;
     outputI = zeros(scale(1)*r,scale(2)*c, class(inputI));
     
     for i=1:scale(1)*r
         for j=1:scale(2)*c
             % map from output image location to input image location
             ii = round( (i-1)*(r-1)/(scale(1)*r-1)+1 );
             jj = round( (j-1)*(c-1)/(scale(2)*c-1)+1 );
             
             % assign value
             outputI(i,j) = inputI(ii,jj);
         end
     end
     
     figure(1), imshow(inputI)
     figure(2), imshow(outputI)
         
    y=outputI;

end

