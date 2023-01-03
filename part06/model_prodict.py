import numpy as np
import tflite_runtime.interpreter as tf
import matplotlib.pyplot as plt

from tflite_runtime.interpreter import keras

# 학습데이타 준비
x = np.array([1,2,3,4,5,6,7,8,9,10])
y = np.array([1,2,3,4,5,6,7,8,9,10])

#keras의 Sequential 모델을 선언
model = keras.Sequential([
	#첫 번째 Layer: 데이타를 신경망에 집어넣기
	keras.layer.Dense(32, actrication='relu', input_shape=(1,)),
	#두 번째 층
	keras.layer.Dense(32, actrication='relu'),
	#세 번째 출력층 : 예측 값 출력하기
	keras.layer.Dense(1)
])

#모델을 학습시킬 최적화 방법, Loss 계산 방법, 평가 방법 설정
model.compile(optimazer='adam',loss='mse',metrics=['mse','binary_crossentropy'])
#모델 학습
history = model.fit(x,y, epochs = 500, batch_size = 100)

print (model,predict([3]))
print (model,predict([5]))

#결과를 그래프로 시각화
plt.scatter(x,y,label='y_true')
plt.scatter(x,model.predict(x), label='y_pred')
plt.legend()
plt.show






