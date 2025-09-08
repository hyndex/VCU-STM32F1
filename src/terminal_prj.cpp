/*
 * File: src/terminal_prj.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/usart.h>
#include "hwdefs.h"
#include "terminal.h"
#include "params.h"
#include "my_string.h"
#include "my_fp.h"
#include "printf.h"
#include "param_save.h"
#include "errormessage.h"
#include "stm32_can.h"
#include "terminalcommands.h"

static void LoadDefaults(Terminal* t, char *arg);
static void GetAll(Terminal* t, char *arg);
static void PrintList(Terminal* t, char *arg);
static void PrintAtr(Terminal* t, char *arg);
static void PrintSerial(Terminal* t, char *arg);
static void PrintErrors(Terminal* t, char *arg);

extern const TERM_CMD TermCmds[] =
{
   { "set", TerminalCommands::ParamSet },
   { "get", TerminalCommands::ParamGet },
   { "flag", TerminalCommands::ParamFlag },
   { "stream", TerminalCommands::ParamStream },
   { "defaults", LoadDefaults },
   { "all", GetAll },
   { "list", PrintList },
   { "atr",  PrintAtr },
   { "save", TerminalCommands::SaveParameters },
   { "load", TerminalCommands::LoadParameters },
   { "json", TerminalCommands::PrintParamsJson },
   { "can", TerminalCommands::MapCan },
   { "serial", PrintSerial },
   { "errors", PrintErrors },
   { "reset", TerminalCommands::Reset },
   { NULL, NULL }
};

static void PrintList(Terminal* t, char *arg)
{
   const Param::Attributes *pAtr;

   arg = arg;

   fprintf(t, "Available parameters and values\r\n");

   for (uint32_t idx = 0; idx < Param::PARAM_LAST; idx++)
   {
      pAtr = Param::GetAttrib((Param::PARAM_NUM)idx);

      if ((Param::GetFlag((Param::PARAM_NUM)idx) & Param::FLAG_HIDDEN) == 0)
         printf("%s [%s]\r\n", pAtr->name, pAtr->unit);
   }
}

static void PrintAtr(Terminal* term, char *arg)
{
   const Param::Attributes *pAtr;

   arg = arg;
   term = term;

   printf("Parameter attributes\r\n");
   printf("Name\t\tmin - max [default]\r\n");

   for (uint32_t idx = 0; idx < Param::PARAM_LAST; idx++)
   {
      pAtr = Param::GetAttrib((Param::PARAM_NUM)idx);
      /* Only display for params */
      if ((Param::GetType((Param::PARAM_NUM)idx) == Param::TYPE_PARAM ||
           Param::GetType((Param::PARAM_NUM)idx) == Param::TYPE_TESTPARAM) &&
          (Param::GetFlag((Param::PARAM_NUM)idx) & Param::FLAG_HIDDEN) == 0)
      {
         printf("%s\t\t%f - %f [%f]\r\n", pAtr->name,pAtr->min,pAtr->max,pAtr->def);
      }
   }
}

static void LoadDefaults(Terminal* t, char *arg)
{
   arg = arg;
   Param::LoadDefaults();
   fprintf(t, "Defaults loaded\r\n");
}

static void GetAll(Terminal* t, char *arg)
{
   const Param::Attributes *pAtr;

   arg = arg;

   for (uint32_t  idx = 0; idx < Param::PARAM_LAST; idx++)
   {
      pAtr = Param::GetAttrib((Param::PARAM_NUM)idx);
      fprintf(t, "%s\t\t%f\r\n", pAtr->name, Param::Get((Param::PARAM_NUM)idx));
   }
}

static void PrintErrors(Terminal* t, char *arg)
{
   t = t;
   arg = arg;
   ErrorMessage::PrintAllErrors();
}

static void PrintSerial(Terminal* t, char *arg)
{
   arg = arg;
   fprintf(t, "%X%X%X\r\n", DESIG_UNIQUE_ID2, DESIG_UNIQUE_ID1, DESIG_UNIQUE_ID0);
}
