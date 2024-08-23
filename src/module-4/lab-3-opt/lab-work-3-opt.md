# Лабораторная работа №3 (Опциональное)

- ## Настройка на коммутаторах протокола PAgP агрегирования каналов технологии EtherChannel

  - ### L2-SW-1

    ```
    L2-SW-1(config)#spanning-tree vlan 1 root primary

    L2-SW-1(config)#int range g0/0-1
    L2-SW-1(config-if-range)#shut
    L2-SW-1(config-if-range)#channel-group 1 mode desirable
    L2-SW-1(config-if-range)#no shut

    L2-SW-1(config)#int range g0/2-3
    L2-SW-1(config-if-range)#shut
    L2-SW-1(config-if-range)#channel-group 2 mode desirable
    L2-SW-1(config-if-range)#no shut

    L2-SW-1(config)#int range g1/0-1
    L2-SW-1(config-if-range)#shut
    L2-SW-1(config-if-range)#channel-group 3 mode desirable
    L2-SW-1(config-if-range)#no shut

    L2-SW-1(config)#int range g1/2-3,g2/0
    L2-SW-1(config-if-range)#shut
    L2-SW-1(config-if-range)#channel-group 4 mode desirable
    L2-SW-1(config-if-range)#no shut
    ```

    ```
    L2-SW-1#sh int stats

    Port-channel4
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor        814      75358          0          0
               Route cache          0          0          0          0
                     Total        814      75358          0          0
    Port-channel3
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor        615      48806          0          0
               Route cache          0          0          0          0
                     Total        615      48806          0          0
    Port-channel2
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1018      69320          0          0
               Route cache          0          0          0          0
                     Total       1018      69320          0          0
    Port-channel1
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor        651      54957          0          0
               Route cache          0          0          0          0
                     Total        651      54957          0          0
    ```

    ```
    L2-SW-1#sh sp

    VLAN0001
      Spanning tree enabled protocol ieee
      Root ID    Priority    24577
               Address     0c69.79be.0000
               This bridge is the root
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

      Bridge ID  Priority    24577  (priority 24576 sys-id-ext 1)
               Address     0c69.79be.0000
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
               Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Po1                 Desg FWD 3         128.65   Shr
    Po2                 Desg FWD 3         128.66   Shr
    Po3                 Desg FWD 3         128.67   Shr
    Po4                 Desg FWD 4         128.68   Shr
    ```

  - ### L2-SW-2

    ```
    L2-SW-2(config)#spanning-tree vlan 1 root secondary

    L2-SW-2(config)#int range g0/0-2
    L2-SW-2(config-if-range)#shut
    L2-SW-2(config-if-range)#channel-group 4 mode auto
    L2-SW-2(config-if-range)#no shut

    L2-SW-2(config)#int range g0/3,g1/0
    L2-SW-2(config-if-range)#shut
    L2-SW-2(config-if-range)#channel-group 5 mode desirable
    L2-SW-2(config-if-range)#no shut

    L2-SW-2(config)#int range g1/1-2
    L2-SW-2(config-if-range)#shut
    L2-SW-2(config-if-range)#channel-group 6 mode desirable
    L2-SW-2(config-if-range)#no shut

    L2-SW-2(config)#int range g1/3,g2/0
    L2-SW-2(config-if-range)#shut
    L2-SW-2(config-if-range)#channel-group 7 mode desirable
    L2-SW-2(config-if-range)#no shut
    ```

    ```
    L2-SW-2#sh int stats

    Port-channel7
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1040      78494          0          0
               Route cache          0          0          0          0
                     Total       1040      78494          0          0
    Port-channel6
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1413      98648          0          0
               Route cache          0          0          0          0
                     Total       1413      98648          0          0
    Port-channel5
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1014      77379          0          0
               Route cache          0          0          0          0
                     Total       1014      77379          0          0
    Port-channel4
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1954     139927          0          0
               Route cache          0          0          0          0
                     Total       1954     139927          0          0
    ```

    ```
    L2-SW-2#sh sp

    VLAN0001
      Spanning tree enabled protocol ieee
      Root ID    Priority    24577
               Address     0c69.79be.0000
               Cost        4
               Port        65 (Port-channel4)
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

      Bridge ID  Priority    28673  (priority 28672 sys-id-ext 1)
               Address     0c6c.13ea.0000
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
               Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Po4                 Root FWD 4         128.65   Shr
    Po5                 Altn BLK 100       128.66   Shr
    Po6                 Altn BLK 3         128.67   Shr
    Po7                 Altn BLK 3         128.68   Shr
    ```

  - ### L2-SW-3

    ```
    L2-SW-3(config)#int range g0/0-1
    L2-SW-3(config-if-range)#shut
    L2-SW-3(config-if-range)#channel-group 1 mode auto
    L2-SW-3(config-if-range)#no shut

    L2-SW-3(config)#int range g0/2-3
    L2-SW-3(config-if-range)#shut
    L2-SW-3(config-if-range)#channel-group 7 mode auto
    L2-SW-3(config-if-range)#no shut
    ```

    ```
    L2-SW-3#sh int stats

    Port-channel7
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1326      97401          0          0
               Route cache          0          0          0          0
                     Total       1326      97401          0          0
    Port-channel1
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1782     119550          0          0
               Route cache          0          0          0          0
                     Total       1782     119550          0          0
    ```

    ```
    L2-SW-3#sh sp

    VLAN0001
      Spanning tree enabled protocol ieee
      Root ID    Priority    24577
               Address     0c69.79be.0000
               Cost        3
               Port        65 (Port-channel1)
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

      Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
               Address     0cc1.9de2.0000
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
               Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Gi1/0               Desg FWD 4         128.5    Shr
    Gi1/1               Desg FWD 4         128.6    Shr
    Po1                 Root FWD 3         128.65   Shr
    Po7                 Desg FWD 3         128.66   Shr
    ```

  - ### L2-SW-4

    ```
    L2-SW-4(config)#int range g0/0-1
    L2-SW-4(config-if-range)#shut
    L2-SW-4(config-if-range)#channel-group 2 mode auto
    L2-SW-4(config-if-range)#no shut

    L2-SW-4(config)#int range g0/2-3
    L2-SW-4(config-if-range)#shut
    L2-SW-4(config-if-range)#channel-group 6 mode auto
    L2-SW-4(config-if-range)#no shut
    ```

    ```
    L2-SW-4#sh int stats

    Port-channel6
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor        727      62878          0          0
               Route cache          0          0          0          0
                     Total        727      62878          0          0
    Port-channel2
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1257      90291          0          0
               Route cache          0          0          0          0
                     Total       1257      90291          0          0
    ```

    ```
    L2-SW-4#sh sp

    VLAN0001
      Spanning tree enabled protocol ieee
      Root ID    Priority    24577
               Address     0c69.79be.0000
               Cost        3
               Port        65 (Port-channel2)
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

     Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
               Address     0c1d.ee4d.0000
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
               Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Gi1/0               Desg FWD 4         128.5    Shr
    Gi1/1               Desg FWD 4         128.6    Shr
    Po2                 Root FWD 3         128.65   Shr
    Po6                 Desg FWD 3         128.66   Shr
    ```

  - ### L2-SW-5

    ```
    L2-SW-5(config)#int range g0/0-1
    L2-SW-5(config-if-range)#shut
    L2-SW-5(config-if-range)#channel-group 3 mode auto
    L2-SW-5(config-if-range)#no shut

    L2-SW-5(config)#int range g0/2-3
    L2-SW-5(config-if-range)#shut
    L2-SW-5(config-if-range)#channel-group 5 mode auto
    L2-SW-5(config-if-range)#no shut
    ```

    ```
    L2-SW-5#sh int stats

    Port-channel5
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1179      87652          0          0
               Route cache          0          0          0          0
                     Total       1179      87652          0          0
    Port-channel3
            Switching path    Pkts In   Chars In   Pkts Out  Chars Out
                 Processor       1666     112550          0          0
               Route cache          0          0          0          0
                     Total       1666     112550          0          0
    ```

    ```
    L2-SW-5#sh sp

    VLAN0001
      Spanning tree enabled protocol ieee
      Root ID    Priority    24577
               Address     0c69.79be.0000
               Cost        3
               Port        65 (Port-channel3)
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

      Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
               Address     0cec.adfb.0000
               Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
               Aging Time  300 sec

    Interface           Role Sts Cost      Prio.Nbr Type
    ------------------- ---- --- --------- -------- --------------------------------
    Gi1/0               Desg FWD 4         128.5    Shr
    Gi1/1               Desg FWD 4         128.6    Shr
    Po3                 Root FWD 3         128.65   Shr
    Po5                 Desg FWD 3         128.66   Shr
    ```

  - ### Схема сети

    ![1](https://github.com/user-attachments/assets/477ebc09-0470-4a02-88a5-0c727ab4f3c9)

- ## Проверка доступности персональных компьютеров

  - ### PC1

    - To PC2

      ```
      PC1> ping 192.168.1.2

      84 bytes from 192.168.1.2 icmp_seq=1 ttl=64 time=0.794 ms
      84 bytes from 192.168.1.2 icmp_seq=2 ttl=64 time=5.586 ms
      84 bytes from 192.168.1.2 icmp_seq=3 ttl=64 time=3.123 ms
      84 bytes from 192.168.1.2 icmp_seq=4 ttl=64 time=0.864 ms
      84 bytes from 192.168.1.2 icmp_seq=5 ttl=64 time=3.115 ms
      ```

    - To PC3

      ```
      PC1> ping 192.168.2.1

      84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=14.879 ms
      84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=7.953 ms
      84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=2.063 ms
      84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=4.729 ms
      84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=7.395 ms
      ```

    - To PC4

      ```
      PC1> ping 192.168.2.2

      84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=13.727 ms
      84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=7.796 ms
      84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=6.983 ms
      84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=16.224 ms
      84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=6.783 ms
      ```

    - To PC5

      ```
      PC1> ping 192.168.3.1

      192.168.3.1 icmp_seq=1 timeout
      84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=8.101 ms
      84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=7.470 ms
      84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=6.371 ms
      84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=3.748 ms
      ```

    - To PC6

      ```
      PC1> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=6.621 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=4.077 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=7.611 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=8.118 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=7.424 ms
      ```

  - ### PC2

    - To PC3

      ```
      PC2> ping 192.168.2.1

      84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=10.735 ms
      84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=6.577 ms
      84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=1.581 ms
      84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=2.579 ms
      84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=8.135 ms
      ```

    - To PC4

      ```
      PC2> ping 192.168.2.2

      192.168.2.2 icmp_seq=1 timeout
      192.168.2.2 icmp_seq=2 timeout
      84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=9.647 ms
      84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=6.994 ms
      84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=13.802 ms
      ```

    - To PC5

      ```
      PC2> ping 192.168.3.1

      84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=12.516 ms
      84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=3.640 ms
      84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=5.990 ms
      84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=1.794 ms
      84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=1.809 ms
      ```

    - To PC6

      ```
      PC2> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=9.537 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=6.911 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=10.082 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=2.143 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=14.853 ms
      ```

  - ### PC3

    - To PC4

      ```
      PC3> ping 192.168.2.2

      84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=15.066 ms
      84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=0.921 ms
      84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=0.898 ms
      84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=4.422 ms
      84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=0.861 ms
      ```

    - To PC5

      ```
      PC3> ping 192.168.3.1

      84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=10.641 ms
      84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=7.579 ms
      84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=3.973 ms
      84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=6.985 ms
      84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=9.267 ms
      ```

    - To PC6

      ```
      PC3> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=8.747 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=6.979 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=8.474 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=1.608 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=6.077 ms
      ```

  - ### PC4

    - To PC5

      ```
      PC4> ping 192.168.3.1

      84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=8.996 ms
      84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=1.624 ms
      84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=9.724 ms
      84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=8.465 ms
      84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=7.749 ms
      ```

    - To PC6

      ```
      PC4> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=8.396 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=6.053 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=8.330 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=6.849 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=7.993 ms
      ```

  - ### PC5

    - To PC6

      ```
      PC5> ping 192.168.3.2

      84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=1.954 ms
      84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=8.329 ms
      84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=6.727 ms
      84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=6.815 ms
      84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=2.312 ms
      ```

- ## Show Running Command Outputs

  - ### L2-SW-1

    ```
    Current configuration : 5715 bytes
    !
    ! Last configuration change at 18:05:18 UTC Fri Aug 23 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-1
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    spanning-tree vlan 1 priority 24576
    !
    vlan internal allocation policy ascending
    !
    vlan 100
     name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel4
     switchport
    !
    interface Port-channel3
     switchport
    !
    interface Port-channel2
     switchport
    !
    interface Port-channel1
     switchport
    !
    interface GigabitEthernet0/0
     media-type rj45
     negotiation auto
     channel-group 1 mode desirable
    !
    interface GigabitEthernet0/1
     media-type rj45
     negotiation auto
     channel-group 1 mode desirable
    !
    interface GigabitEthernet0/2
     media-type rj45
     negotiation auto
     channel-group 2 mode desirable
    !
    interface GigabitEthernet0/3
     media-type rj45
     negotiation auto
     channel-group 2 mode desirable
    !
    interface GigabitEthernet1/0
     media-type rj45
     negotiation auto
     channel-group 3 mode desirable
    !
    interface GigabitEthernet1/1
     media-type rj45
     negotiation auto
     channel-group 3 mode desirable
    !
    interface GigabitEthernet1/2
     media-type rj45
     negotiation auto
     channel-group 4 mode desirable
    !
    interface GigabitEthernet1/3
     media-type rj45
     negotiation auto
     channel-group 4 mode desirable
    !
    interface GigabitEthernet2/0
     media-type rj45
     negotiation auto
     channel-group 4 mode desirable
    !
    ip forward-protocol nd
    !
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
    ```

  - ### L2-SW-2

    ```
    Current configuration : 5715 bytes
    !
    ! Last configuration change at 18:05:21 UTC Fri Aug 23 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-2
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    spanning-tree vlan 1 priority 28672
    !
    vlan internal allocation policy ascending
    !
    vlan 100
     name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel7
     switchport
    !
    interface Port-channel6
     switchport
    !
    interface Port-channel5
     switchport
    !
    interface Port-channel4
     switchport
    !
    interface GigabitEthernet0/0
     media-type rj45
     negotiation auto
     channel-group 4 mode auto
    !
    interface GigabitEthernet0/1
     media-type rj45
     negotiation auto
     channel-group 4 mode auto
    !
    interface GigabitEthernet0/2
     media-type rj45
     negotiation auto
     channel-group 4 mode auto
    !
    interface GigabitEthernet0/3
     media-type rj45
     negotiation auto
     channel-group 5 mode desirable
    !
    interface GigabitEthernet1/0
     media-type rj45
     negotiation auto
     channel-group 5 mode desirable
    !
    interface GigabitEthernet1/1
     media-type rj45
     negotiation auto
     channel-group 6 mode desirable
    !
    interface GigabitEthernet1/2
     media-type rj45
     negotiation auto
     channel-group 6 mode desirable
    !
    interface GigabitEthernet1/3
     media-type rj45
     negotiation auto
     channel-group 7 mode desirable
    !
    interface GigabitEthernet2/0
     media-type rj45
     negotiation auto
     channel-group 7 mode desirable
    !
    ip forward-protocol nd
    !
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
    ```

  - ### L2-SW-3

    ```
    Current configuration : 5223 bytes
    !
    ! Last configuration change at 18:05:24 UTC Fri Aug 23 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-3
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    !
    vlan internal allocation policy ascending
    !
    vlan 100
     name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel7
     switchport
    !
    interface Port-channel1
     switchport
    !
    interface GigabitEthernet0/0
     media-type rj45
     negotiation auto
     channel-group 1 mode auto
    !
    interface GigabitEthernet0/1
     media-type rj45
     negotiation auto
     channel-group 1 mode auto
    !
    interface GigabitEthernet0/2
     media-type rj45
     negotiation auto
     channel-group 7 mode auto
    !
    interface GigabitEthernet0/3
     media-type rj45
     negotiation auto
     channel-group 7 mode auto
    !
    interface GigabitEthernet1/0
     media-type rj45
     negotiation auto
    !
    interface GigabitEthernet1/1
     media-type rj45
     negotiation auto
    !
    ip forward-protocol nd
    !
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
    ```

  - ### L2-SW-4

    ```
    Current configuration : 5223 bytes
    !
    ! Last configuration change at 18:05:26 UTC Fri Aug 23 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-4
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    !
    vlan internal allocation policy ascending
    !
    vlan 100
     name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel6
     switchport
    !
    interface Port-channel2
     switchport
    !
    interface GigabitEthernet0/0
     media-type rj45
     negotiation auto
     channel-group 2 mode auto
    !
    interface GigabitEthernet0/1
     media-type rj45
     negotiation auto
     channel-group 2 mode auto
    !
    interface GigabitEthernet0/2
     media-type rj45
     negotiation auto
     channel-group 6 mode auto
    !
    interface GigabitEthernet0/3
     media-type rj45
     negotiation auto
     channel-group 6 mode auto
    !
    interface GigabitEthernet1/0
     media-type rj45
     negotiation auto
    !
    interface GigabitEthernet1/1
     media-type rj45
     negotiation auto
    !
    ip forward-protocol nd
    !
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
    ```

  - ### L2-SW-5

    ```
    Current configuration : 5223 bytes
    !
    ! Last configuration change at 18:05:27 UTC Fri Aug 23 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-5
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    !
    vlan internal allocation policy ascending
    !
    vlan 100
     name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel5
     switchport
    !
    interface Port-channel3
     switchport
    !
    interface GigabitEthernet0/0
     media-type rj45
     negotiation auto
     channel-group 3 mode auto
    !
    interface GigabitEthernet0/1
     media-type rj45
     negotiation auto
     channel-group 3 mode auto
    !
    interface GigabitEthernet0/2
     media-type rj45
     negotiation auto
     channel-group 5 mode auto
    !
    interface GigabitEthernet0/3
     media-type rj45
     negotiation auto
     channel-group 5 mode auto
    !
    interface GigabitEthernet1/0
     media-type rj45
     negotiation auto
    !
    interface GigabitEthernet1/1
     media-type rj45
     negotiation auto
    !
    ip forward-protocol nd
    !
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
    ```
