/*
 * File: src/heater_lin_a.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



 #include <heater_lin_a.h>

 static uint8_t processedPower=0;
 static uint8_t TenCount=0;


 void HeaterLinA::SetLinInterface(LinBus* l)
 {
    lin = l;
    DigIo::lin_wake.Clear();//Not used on TJA1027
    DigIo::lin_nslp.Set();//Wakes the device
    //Johannes for president!

 }

 void HeaterLinA::SetPower(uint16_t power, bool HeatReq)
{
    TenCount++;
    if(TenCount==5)//slow down to 50ms as this is called in 10ms task.
    {
    TenCount=0;
    HeatReq=HeatReq;
   //going to ignore heatreq just for test.

   if(power>=255) power = 255;//Constrain power to max for VW heater.
   processedPower=power;//10;

   static bool read = true;

   if (lin->HasReceived(48, 8))//0x30 hex address
   {
      uint8_t* data = lin->GetReceivedBytes();

      Param::SetFloat(Param::tmpheater, data[6]-47);//Looks like the temp val has an offset prob for neg vals. Need to get it more accurate
      Param::SetFloat(Param::udcheater, data[4]/10);//0x8D = 141 dec /10 =14.1V ? 12v system voltage.
      Param::SetFloat(Param::powerheater,data[0]*80);//actual power used by heater. again, needs some more experiments to get more accurate
   }

   if (read)
   {
      lin->Request(48, 0, 0);//0x30 hex address
   }
   else
   {
      uint8_t lindata[4];
      lindata[0] = Param::GetInt(Param::HeatPercnt);//VW heater uses a % setting as opposed to a set power val. Regulates its temps to this.
      lindata[1] = 1;//Always on for test. Can use heatreq here.
      lindata[2] = 0;
      lindata[3] = 0;
      lin->Request(28, lindata, sizeof(lindata));//0x1C hex address
   }

   read = !read;
   }
}
