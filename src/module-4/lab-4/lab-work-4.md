# Лабораторная работа №4

- ## Настройка на коммутаторах логической топологии используя протокол IEEE 802.1Q

  - ### L2-SW-1, L2-SW-2

  ```
  vlan 20
  name VLAN20
  exit
  vlan 333
  name VLAN333
  exit

  int range g0/0-3
  shut
  switchport trunk encapsulation dot1q
  switchport trunk native vlan 333
  switchport mode trunk
  no shut
  exit

  int range g1/0-3
  shut
  switchport trunk encapsulation dot1q
  switchport trunk native vlan 333
  switchport mode trunk
  no shut
  exit

  spanning-tree vlan 20,333 root primary / secondary
  ```

  - ### L2-SW-3, L2-SW-4, L2-SW-5

  ```
  vlan 20
  name VLAN20
  exit
  vlan 333
  name VLAN333
  exit

  int range g0/0-3
  shut
  switchport trunk encapsulation dot1q
  switchport trunk native vlan 333
  switchport mode trunk
  no shut
  exit

  int g1/0
  shut
  switchport mode access
  switchport access vlan 20
  no shut
  exit
  int g1/1
  shut
  switchport mode access
  switchport access vlan 333
  no shut
  exit
  ```

  - ### Схема сети

  ![1](https://github.com/user-attachments/assets/e83ce2cb-0807-4355-b364-9ed195cfde55)

- ## Проверка доступности персональных компьютеров

  - ### PC1

    - To PC2

    ```
    PC1> ping 192.168.1.2

    host (192.168.1.2) not reachable
    ```

    - To PC3

    ```
    PC1> ping 192.168.2.1

    84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=15.722 ms
    84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=6.837 ms
    84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=7.954 ms
    84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=3.898 ms
    84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=1.948 ms
    ```

    - To PC4

    ```
    PC1> ping 192.168.2.2

    host (192.168.2.2) not reachable
    ```

    - To PC5

    ```
    PC1> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=9.198 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=5.519 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=7.122 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=7.295 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=7.409 ms
    ```

    - To PC6

    ```
    PC1> ping 192.168.3.2

    host (192.168.3.2) not reachable
    ```

  - ### PC2

    - To PC3

    ```
    PC2> ping 192.168.2.1

    host (192.168.2.1) not reachable
    ```

    - To PC4

    ```
    PC2> ping 192.168.2.2

    84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=6.300 ms
    84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=7.769 ms
    84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=6.838 ms
    84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=6.340 ms
    84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=7.459 ms
    ```

    - To PC5

    ```
    PC2> ping 192.168.3.1

    host (192.168.3.1) not reachable
    ```

    - To PC6

    ```
    PC2> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=10.107 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=7.374 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=5.063 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=7.512 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=13.720 ms
    ```

  - ### PC3

    - To PC4

    ```
    PC3> ping 192.168.2.2

    host (192.168.2.2) not reachable
    ```

    - To PC5

    ```
    PC3> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=12.363 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=6.695 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=6.125 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=5.094 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=6.932 ms
    ```

    - To PC6

    ```
    PC3> ping 192.168.3.2

    host (192.168.3.2) not reachable
    ```

  - ### PC4

    - To PC5

    ```
    PC4> ping 192.168.3.1

    host (192.168.3.1) not reachable
    ```

    - To PC6

    ```
    PC4> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=4.335 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=6.939 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=4.280 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=3.755 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=6.591 ms
    ```

  - ### PC5

    - To PC6

    ```
    PC5> ping 192.168.3.2

    host (192.168.3.2) not reachable
    ```
