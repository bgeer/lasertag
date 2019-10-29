#include "hwlib.hpp"
#include "terminal.hpp"


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

   // Make keypad
    

   // Make terminal
   auto oled_terminal = terminal(oled);






   // // Test oled with strings
   // oled_terminal.write("Hallo");
   // oled_terminal.write("ik ben daan");
   // oled_terminal.write("Vandaag gaan we");
   // oled_terminal.write("dingen doen");
   // oled_terminal.write("toch?");
   // oled_terminal.write("waaromniet?");
   // oled_terminal.write("gekke jinkel");
   // oled_terminal.write("kinkelburg");

   // hwlib::wait_ms(1000);

   // oled_terminal.write("OPEN JE LIJST");
   // oled_terminal.write("pieper");
   // oled_terminal.write("fusion69");
   // oled_terminal.write("wovo");
   // oled_terminal.write("heeft een kind");
   // oled_terminal.write("en die heet wovi");
   // oled_terminal.write("en een vrouw");
   // oled_terminal.write("wovina ;)");

   // hwlib::wait_ms(3000);

   // oled_terminal.clear();

   //oled_terminal.add("Jinkselburgerino");
   //oled_terminal.write();

   hwlib::wait_ms(3000);

   oled_terminal.clear();
   for (int i = 0; true; i++) {
      hwlib::string<16> s= "";
      hwlib::string<1> c = keypad.getc();
      s += c;
      oled_terminal.write(s);
   }





   // auto w1 = hwlib::part( 
   //    oled, 
   //    hwlib::xy( 0, 0 ),
   //    hwlib::xy( 128, 32));
   // auto w2 = hwlib::part( 
   //    oled, 
   //    hwlib::xy( 0, 32 ),
   //    hwlib::xy( 128, 32));
      
   // auto f1 = hwlib::font_default_16x16();
   // auto d1 = hwlib::terminal_from( w1, f1 );
   
   // auto f2 = hwlib::font_default_8x8();
   // auto d2 = hwlib::terminal_from( w2, f2 );
   
   // d1 << "\f"
   //    << "LASER \nshooter";   
   // d2 << "\f"
   //    << "================\n"
   //    << "user: Mark4\n"
   //    << "score: " << 42 << "\n"
   //    << "================\n";     
      
   // auto t1 = hwlib::now_us(); 
   // oled.flush();
   // auto t2 = hwlib::now_us();
   // HWLIB_TRACE << "oled.flush() took " << t2 - t1 << " us";
      
   // int n = 0;   
   // for(;;){
   //    hwlib::wait_ms( 1000 );
   //    d1 << "\f" << ++n;
   //    d2 << "\t0502" << ": " << n + 42;
   //    oled.flush();
   // }      
      
}
