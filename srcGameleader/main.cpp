#include "hwlib.hpp"
#include "terminal.hpp"
#include "gameLeaderController.hpp"
#include "/home/daanzvw/LazerGameProject/lasertag/srcSender/irLedController.hpp"
#include "gameLeaderController.hpp"


int main( void ){
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;

   // Wait for the PC console to start
   hwlib::wait_ms( 500 );   
   
   namespace target = hwlib::target;
   
   // Display config
   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled = hwlib::glcd_oled( i2c_bus, 0x3c );

   // Keypad config
   auto out0 = target::pin_oc( target::pins::a3 );
   auto out1 = target::pin_oc( target::pins::a2 );
   auto out2 = target::pin_oc( target::pins::a1 );
   auto out3 = target::pin_oc( target::pins::a0 );

   auto in0  = target::pin_in( target::pins::a7 );
   auto in1  = target::pin_in( target::pins::a6 );
   auto in2  = target::pin_in( target::pins::a5 );
   auto in3  = target::pin_in( target::pins::a4 );
   
   auto out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
   auto in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
   auto matrix   = hwlib::matrix_of_switches( out_port, in_port );
   auto keypad   = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );

   // Make terminal
   auto start1 = hwlib::xy(0,0);
   auto end1 = hwlib::xy(128, 32);
   auto oled_terminal1 = terminal(oled,start1,end1); 

   auto start2 = hwlib::xy(0,32);
   auto end2 = hwlib::xy(128, 64);
   auto oled_terminal2 = terminal(oled,start2,end2); 

   //oled_terminal1.writethings();

   auto ir  = irLed();
   auto sender = irLedSender(ir);

   auto gameleadercontroller = gameLeaderController(sender, oled_terminal1, oled_terminal2, keypad);
   gameleadercontroller.playerconfig();
   
   // hwlib::string<10> text = "Hallo Daan";
   // oled_terminal.write8x8(text);
   // oled_terminal.flush();  

   // start = start + hwlib::xy(0, 32);
   // end = end + hwlib::xy(0, 32);
   // text = "Hallo\nDaan";
   // oled_terminal.write16x16( text );   
}
