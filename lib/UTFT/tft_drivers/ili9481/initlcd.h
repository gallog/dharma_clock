

case ILI9481:
	LCD_Write_COM(0x11); //0x11
	delay(20);
	LCD_Write_COM(0xD0);   //(0xD0)
	LCD_Write_DATA(0x07);  //(0x07)
	LCD_Write_DATA(0x41);  //(0x42)
	LCD_Write_DATA(0x1D);  //(0x1B)

	LCD_Write_COM(0xD1);   //(0xD1)
	LCD_Write_DATA(0x00);  //(0x00)
	LCD_Write_DATA(0x2B);  //(0x07)
	LCD_Write_DATA(0x1F);  //(0x10)

	LCD_Write_COM(0xD2);   //(0xD2)
	LCD_Write_DATA(0x01);  //(0x01)
	LCD_Write_DATA(0x11);  //(0x02)

	LCD_Write_COM(0xC0);   //(0xC0) //Panel Driving Setting / Set Default Gamma
	LCD_Write_DATA(0x00);  //(0x10)
	LCD_Write_DATA(0x3B);  //(0x3B)
	LCD_Write_DATA(0x00);  //(0x00)
	LCD_Write_DATA(0x02);  //(0x02)
	LCD_Write_DATA(0x11);  //(0x11)

//Display_Timing_Setting for Normal Mode
        LCD_Write_COM(0xC1);	//
	LCD_Write_DATA(0x10);	//Line inversion,DIV1[1:0]
	LCD_Write_DATA(0x10);	//RTN1[4:0]
	LCD_Write_DATA(0x88);	//BP and FP


	LCD_Write_COM(0xC5);   //(0xC5) //Frame Rate Control / Set frame rate
	LCD_Write_DATA(0x03);  //(0x03)

 	LCD_Write_COM(0xB6);		// Display Function Control
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x22);		// 0x42 = Rotate display 180 deg.
	LCD_Write_DATA(0x3B);


	LCD_Write_COM(0xC8);   //(0xC8) //Gamma Setting / Set Gamma
	LCD_Write_DATA(0x00);  //(0x18)
	LCD_Write_DATA(0x14);  //(0x32)
	LCD_Write_DATA(0x33);  //(0x36)
	LCD_Write_DATA(0x10);  //(0x45)
	LCD_Write_DATA(0x00);  //(0x06)
	LCD_Write_DATA(0x16);  //(0x18)
	LCD_Write_DATA(0x44);  //(0x37)
	LCD_Write_DATA(0x36);  //(0x75)
	LCD_Write_DATA(0x77);  //(0x77)
	LCD_Write_DATA(0x00);  //(0x54)
	LCD_Write_DATA(0x0F);  //(0x0C)
	LCD_Write_DATA(0x00);  //(0x00)

        LCD_Write_COM(0x21);   // Display Inversion ON 0x21
	LCD_Write_DATA(0xC8);  // C8 	

        LCD_Write_COM(0xE4);   //
	LCD_Write_DATA(0xA0);  //

        LCD_Write_COM(0xF0);   //
	LCD_Write_DATA(0x01);  //

//======RGB IF setting========
//RGB OR SYS INTERFACE
        LCD_Write_COM(0xB4);
	LCD_Write_DATA(0x10);//RGB

        LCD_Write_COM(0xC6);
	LCD_Write_DATA(0x1B);
//============================


	LCD_Write_COM(0x36);   //(0x36) //set_address_mode MIROR IMAGE LENDSCAPE
	LCD_Write_DATA(0x4A); //D);  //(0x0D) MIROR AND ORIENTATION IMAGE
//Page Address Order:Top to Bottom,Column Address Order:Right to Left,Page/Column Order:Normal Mode,Line Address Order:LCD Refresh Top to Bottom

	LCD_Write_COM(0x3A);   //(0x3A) //set_pixel_format
	LCD_Write_DATA(0x55);  //(0x55) //DBI:16bit/pixel (65,536 colors)

	LCD_Write_COM(0x2A);   //(0x2A) //set_column_address
	LCD_Write_DATA(0x00);  //(0x18)
	LCD_Write_DATA(0x00);  //(0x18)
	LCD_Write_DATA(0x01);  //(0x18)
	LCD_Write_DATA(0x3F);  //(0x18)

	LCD_Write_COM(0x2B);   //(0x2B) //set_page_address
	LCD_Write_DATA(0x00);  //(0x18)
	LCD_Write_DATA(0x00);  //(0x00)
	LCD_Write_DATA(0x01);  //(0x01)
	LCD_Write_DATA(0xE0);  //(0xE0)

	LCD_Write_COM(0x13);		//NORMAL DISPLAY

        delay(120);
	LCD_Write_COM(0x29);   //(0x29) //set_display_on / display on
	break;