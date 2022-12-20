import scapy.all as scapy


def sniff(interface):
    scapy.sniff(iface=interface, store=False, prn=process_sniffed_packet)


def process_sniffed_packet(packet):
    if packet.haslayer(scapy.TCP):
        print("\n\nОтправитель >> " + packet[scapy.IP].src + "\nПолучатель >> " + packet[scapy.IP].dst)
        print(f"\nТеги TCP:\n\tsport = {packet[scapy.TCP].sport}\n\tdport = {packet[scapy.TCP].dport}\n\t"
              f"seq = {packet[scapy.TCP].seq}\n\tack = {packet[scapy.TCP].ack}\n\t"
              f"dataofs = {packet[scapy.TCP].dataofs}\n\treserved = {packet[scapy.TCP].reserved}\n\t"
              f"flags = {packet[scapy.TCP].flags}\n\twindow = {packet[scapy.TCP].window}\n\t"
              f"chksum = {packet[scapy.TCP].chksum}\n\turgptr = {packet[scapy.TCP].urgptr}\n\t"
              f"options = {packet[scapy.TCP].options}")
        # packet.show()


sniff('Realtek 8821CE Wireless LAN 802.11ac PCI-E NIC')
