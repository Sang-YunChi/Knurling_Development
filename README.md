# Knurling_Development_Team


# 실행에 앞서
1. 본 프로그램을 실행하려면 apmsetup이 설치돼있어야한다.
2. 먼저 MEGA-UNO 를 블루투스 연결하여 통신가능하게 하고, MEGA-PIN을 블루투스 연결하여 통신가능하게 한다.
3. html,css 그리고 php 파일은 C:\APM_Setup\htdocs 의 폴더에 넣어준다.

# 컴파일
1. 무게 측정 센서에 Mega_Code_Pin.ino 을 컴파일 한다.
2. rfid 센서에 uno_rfid.ino 을 컴파일 한다.
3. 메인 센서에 Mega_Code_Main.ino을 컴파일 한다

# 작동 방법
1. 먼저 휴대폰이나 카드 키를 rfid에 찍는다. 이때 블루투스 모듈은 사용자 정보(rfid 정보) 를 메인 센서 (MEGA)에 보낸다.
2. 무게 핀을 본인이 원하는 무게에 버튼을 누르며 장착한다.
3. 정자세로 운동을 한다.
4. html에 실시간으로 count 개수, 무게, 이름, rfid 정보가 실시간으로 송출된다.
      
