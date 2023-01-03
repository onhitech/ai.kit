import cv2

face_cascade = cv2.CascadeClassifier('/home/pi/opencv/haarcascade_frontalface_alt.xml')
cap = cv2.VideoCapture(-1)
while(True):
	ret, frame = cap.read()
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	rects = face_cascade.detectMultiScale(gray, 1.3, 5)
	for (x, y, w, h) in rects:
		cv2.rectangle(frame, (x, y), (x+w, y+h), (0,255,0), 3)
	cv2.imshow('Face', frame)
	k = cv2.waitKey(1) 	# keyboard입력을 대기하는 함수
	if k == 27: 		# esc key
		break
cap.release()
cv2.destroyAllWindows() # 화면 나타난 윈도우 종료