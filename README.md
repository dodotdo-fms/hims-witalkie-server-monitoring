hims-packet-monitor
===================

서버에 설치 후 사용합니다.


## 컴파일 (Ubuntu 기준)

```bash
sudo apt-get install -y libasio-dev libpcap-dev

git clone git@github.com:dodotdo/hims-witalkie-server-monitoring.git

cd hims-witalkie-server-monitoring
mkdir build
cd build

cmake ..
make
```


## 사용법

`hims-packet-monitor [ifdev] [signal-port] [audio-port]`

ifdev
:    패킷을 주고받게 될 이더넷의 이름

signal-port (기본값: 0)
:    모니터링할 TCP 포트(0 == 모니터링 하지 않음)

audio-port (기본값: 0)
:    모니터링할 UDP 포트(0 == 모니터링 하지 않음)

### 설치된 이더넷 목록 출력

```bash
$ sudo hims-packet-monitor
```


### 사용예

```bash
$ sidp hims-packet-monitor eth0 4000 4001
```

eth0 이더넷에서 signal-port(4000), audio-port(4001) 을 대기하고 주고받는 패킷의 이름을 화면에 표시합니다.


## 화면 설명

SYN=1
:    연결 시도

FIN=1
:    연결 종료

RST=1
:    연결 취소
