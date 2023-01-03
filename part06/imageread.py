import cv2

img_file = "apple.jpg" #이미지 경로설정
save_img = "apple_gray.jpg" # 저장할 경로설정

img = cv2.imread(img_file, cv2.IMREAD_GRAYSCALE) #이미지를 그레이모드로 읽어 변수로 할당

if img is not None:
    cv2.imshow('IMG',img)           #이미지 화면에 표시
    cv2.imwrite(save_img,img)  		#이미지 저장
    cv2.waitKey()                   #키입력까지 대기
    cv2.destroyAllWindows()         #창닫기
else:
    print("Don't found image file")