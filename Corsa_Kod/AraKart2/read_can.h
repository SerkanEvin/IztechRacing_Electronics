

void read_can_messages() {
  if (msgRx.id == make_j1939_id(4, 0xF420, 0x83)) {
    send_speed_datas_to_screen();
  } else if (msgRx.id == make_j1939_id(4, 0xF350, 0x82)) {
    send_acc_datas_to_screen();
  } else if (msgRx.id == make_j1939_id(4, 0xF600, 0x80) || msgRx.id == make_j1939_id(6, 0xF700, 0x82) || msgRx.id == make_j1939_id(6, 0xF500, 0x83)) {
    send_kart_online();
  }
}