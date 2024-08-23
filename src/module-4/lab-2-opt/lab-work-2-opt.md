# Лабораторная работа №2 (Опциональное)

- ## Настройка протокола RSTP

  - ### L2-SW-1

    ```
    vIOS-L2-01#conf t
    vIOS-L2-01(config)#int range g0/0-3
    vIOS-L2-01(config-if-range)#shut
    vIOS-L2-01(config-if-range)#switchport trunk encapsulation dot1q
    vIOS-L2-01(config-if-range)#switchport trunk native vlan 1
    vIOS-L2-01(config-if-range)#switchport mode trunk
    vIOS-L2-01(config-if-range)#no shut
    vIOS-L2-01(config-if-range)#exit
    vIOS-L2-01(config)#int range g1/0-3
    vIOS-L2-01(config-if-range)#shut
    vIOS-L2-01(config-if-range)#switchport trunk encapsulation dot1q
    vIOS-L2-01(config-if-range)#switchport trunk native vlan 1
    vIOS-L2-01(config-if-range)#switchport mode trunk
    vIOS-L2-01(config-if-range)#no shut
    vIOS-L2-01(config-if-range)#exit
    vIOS-L2-01(config)#hostname L2-SW-1
    L2-SW-1(config)#spanning-tree vlan 1 root primary
    L2-SW-1(config)#spanning-tree mode rapid-pvst

    L2-SW-1#sh sp
    VLAN0001
      Spanning tree enabled protocol rstp
      Root ID    Priority    24577
             Address     0c87.dc96.0000
             This bridge is the root
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

      Bridge ID  Priority    24577  (priority 24576 sys-id-ext 1)
             Address     0c87.dc96.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Gi0/0               Desg FWD 4         128.1    Shr
    Gi0/1               Desg FWD 4         128.2    Shr
    Gi0/2               Desg FWD 4         128.3    Shr
    Gi0/3               Desg FWD 4         128.4    Shr
    Gi1/0               Desg FWD 4         128.5    Shr
    Gi1/1               Desg FWD 4         128.6    Shr
    Gi1/2               Desg FWD 4         128.7    Shr
    Gi1/3               Desg FWD 4         128.8    Shr
    ```

  - ### L2-SW-2

    ```
    vIOS-L2-01#conf t
    vIOS-L2-01(config)#int range g0/0-3
    vIOS-L2-01(config-if-range)#shut
    vIOS-L2-01(config-if-range)#switchport trunk encapsulation dot1q
    vIOS-L2-01(config-if-range)#switchport trunk native vlan 1
    vIOS-L2-01(config-if-range)#switchport mode trunk
    vIOS-L2-01(config-if-range)#no shut
    vIOS-L2-01(config-if-range)#exit
    vIOS-L2-01(config)#int range g1/0-3
    vIOS-L2-01(config-if-range)#shut
    vIOS-L2-01(config-if-range)#switchport trunk encapsulation dot1q
    vIOS-L2-01(config-if-range)#switchport trunk native vlan 1
    vIOS-L2-01(config-if-range)#switchport mode trunk
    vIOS-L2-01(config-if-range)#no shut
    vIOS-L2-01(config-if-range)#exit
    vIOS-L2-01(config)#hostname L2-SW-2
    L2-SW-2(config)#spanning-tree vlan 1 root secondary
    L2-SW-2(config)#spanning-tree mode rapid-pvst

    L2-SW-2#sh sp
    VLAN0001
      Spanning tree enabled protocol rstp
      Root ID    Priority    24577
             Address     0c87.dc96.0000
             Cost        4
             Port        1 (GigabitEthernet0/0)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

      Bridge ID  Priority    28673  (priority 28672 sys-id-ext 1)
             Address     0c2a.271c.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Gi0/0               Root FWD 4         128.1    Shr
    Gi0/1               Altn BLK 4         128.2    Shr
    Gi0/2               Desg FWD 4         128.3    Shr
    Gi0/3               Desg FWD 4         128.4    Shr
    Gi1/0               Desg FWD 4         128.5    Shr
    Gi1/1               Desg FWD 4         128.6    Shr
    Gi1/2               Desg FWD 4         128.7    Shr
    Gi1/3               Desg FWD 4         128.8    Shr
    ```

  - ### L2-SW-3, L2-SW-4, L2-SW-5

    ```
    vIOS-L2-01#conf t
    vIOS-L2-01(config)#int range g0/0-3
    vIOS-L2-01(config-if-range)#shut
    vIOS-L2-01(config-if-range)#switchport trunk encapsulation dot1q
    vIOS-L2-01(config-if-range)#switchport trunk native vlan 1
    vIOS-L2-01(config-if-range)#switchport mode trunk
    vIOS-L2-01(config-if-range)#no shut
    vIOS-L2-01(config-if-range)#exit
    vIOS-L2-01(config)#int range g1/0-1
    vIOS-L2-01(config-if-range)#shut
    vIOS-L2-01(config-if-range)#switchport mode access
    vIOS-L2-01(config-if-range)#switchport access vlan 1
    vIOS-L2-01(config-if-range)#no shut
    vIOS-L2-01(config-if-range)#exit
    vIOS-L2-01(config)#spanning-tree mode rapid-pvst
    vIOS-L2-01(config)#exit
    ```

  - ### Схема сети

    ![1](https://github.com/user-attachments/assets/cfc699ae-4b5e-416e-9f51-cdbcc9aea3c6)

- ## Проверка доступности персональных компьютеров

  - ### PC1

    - To PC2

      ```
      PC1> ping 192.168.1.2

      84 bytes from 192.168.1.2 icmp_seq=1 ttl=64 time=13.010 ms
      84 bytes from 192.168.1.2 icmp_seq=2 ttl=64 time=7.136 ms
      84 bytes from 192.168.1.2 icmp_seq=3 ttl=64 time=3.764 ms
      84 bytes from 192.168.1.2 icmp_seq=4 ttl=64 time=2.885 ms
      84 bytes from 192.168.1.2 icmp_seq=5 ttl=64 time=0.884 ms
      ```

    - To PC3

      ```
      PC1> ping 192.168.2.1

      84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=18.537 ms
      84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=8.552 ms
      84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=6.506 ms
      84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=7.265 ms
      84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=9.221 ms
      ```

    - To PC4

      ```
      PC1> ping 192.168.2.2

      84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=18.532 ms
      84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=12.040 ms
      84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=10.263 ms
      84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=5.898 ms
      84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=10.034 ms
      ```

    - To PC5

      ```
      PC1> ping 192.168.3.1

      84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=12.087 ms
      84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=15.016 ms
      84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=4.107 ms
      84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=3.334 ms
      84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=7.016 ms
      ```

    - To PC6

      ```
      PC1> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=10.438 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=7.377 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=2.472 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=9.018 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=7.234 ms
      ```

  - ### PC2

    - To PC3

      ```
      PC2> ping 192.168.2.1

      84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=11.325 ms
      84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=7.716 ms
      84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=3.728 ms
      84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=1.594 ms
      84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=8.062 ms
      ```

    - To PC4

      ```
      PC2> ping 192.168.2.2

      84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=4.704 ms
      84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=9.601 ms
      84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=6.659 ms
      84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=7.190 ms
      84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=7.174 ms
      ```

    - To PC5

      ```
      PC2> ping 192.168.3.1

      84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=12.247 ms
      84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=1.758 ms
      84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=5.085 ms
      84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=4.001 ms
      84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=2.898 ms
      ```

    - To PC6

      ```
      PC2> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=7.911 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=7.029 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=6.130 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=8.833 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=14.157 ms
      ```

  - ### PC3

    - To PC4

      ```
      PC3> ping 192.168.2.2

      84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=8.504 ms
      84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=1.675 ms
      84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=4.166 ms
      84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=7.835 ms
      84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=0.848 ms
      ```

    - To PC5

      ```
      PC3> ping 192.168.3.1

      84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=5.344 ms
      84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=1.736 ms
      84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=4.558 ms
      84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=13.699 ms
      84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=8.661 ms
      ```

    - To PC6

      ```
      PC3> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=10.599 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=8.535 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=2.396 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=7.258 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=7.573 ms
      ```

  - ### PC4

    - To PC5

      ```
      PC4> ping 192.168.3.1

      84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=9.569 ms
      84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=6.692 ms
      84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=5.618 ms
      84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=5.887 ms
      84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=7.450 ms
      ```

    - To PC6

      ```
      PC4> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=8.311 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=1.773 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=3.944 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=4.120 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=7.876 ms
      ```

  - ### PC5

    - To PC6

      ```
      PC5> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=10.119 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=0.801 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=6.130 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=6.378 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=4.893 ms
      ```

- ## Изменить стоимость маршрута для порта RP

  - ### Изначальная схема с базовой конфигурацией L2-SW-4

    ```
    L2-SW-4#sh sp

    VLAN0001
      Spanning tree enabled protocol rstp
      Root ID    Priority    24577
             Address     0c87.dc96.0000
             Cost        4
             Port        1 (GigabitEthernet0/0)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

      Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     0cb8.17f2.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Gi0/0               Root FWD 4         128.1    Shr
    Gi0/1               Altn BLK 4         128.2    Shr
    Gi0/2               Altn BLK 4         128.3    Shr
    Gi0/3               Altn BLK 4         128.4    Shr
    Gi1/0               Desg FWD 4         128.5    Shr
    Gi1/1               Desg FWD 4         128.6    Shr
    ```

  - ### Конфигурация L2-SW-4

    ```
    # После изменений маршрут потока изменится с L2-SW-4 -> L2-SW-1 на L2-SW-4 -> L2-SW-2 -> L2-SW-1
    L2-SW-4#conf t
    L2-SW-4(config)#int range g0/0-1
    L2-SW-4(config-if)#span vlan 1 cost 24
    L2-SW-4(config-if)#no shut
    L2-SW-4(config-if)#exit
    ```

  - ### Вывод измененной схемы

    ```
    L2-SW-4#sh sp

    VLAN0001
      Spanning tree enabled protocol rstp
      Root ID    Priority    24577
             Address     0c87.dc96.0000
             Cost        8
             Port        3 (GigabitEthernet0/2)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

      Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     0cb8.17f2.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Gi0/0               Altn BLK 24        128.1    Shr
    Gi0/1               Altn BLK 24        128.2    Shr
    Gi0/2               Root FWD 4         128.3    Shr
    Gi0/3               Altn BLK 4         128.4    Shr
    Gi1/0               Desg LRN 4         128.5    Shr
    Gi1/1               Desg LRN 4         128.6    Shr
    ```

    ![2](https://github.com/user-attachments/assets/5ab6d64f-7bb0-4724-85a3-af7f2336111f)
