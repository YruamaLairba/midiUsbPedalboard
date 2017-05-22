#include "preset.h"

//ctor
Preset::Preset(){}

//void Preset::init()
//{
//}

FsMode Preset::get_fsMode(uint8_t fsNumber)
{
  if (fsNumber < nbFsConfigs)
  {
    return fsConfigs[fsNumber].fsMode;
  }
  else
  {
    return 0xFF; //error code
  }
}

void Preset::set_fsMode(uint8_t fsNumber, FsMode fsMode)
{
  if (fsNumber < nbFsConfigs)
  {
    if (fsConfigs[fsNumber].fsMode != fsMode)
    {
      fsConfigs[fsNumber].fsMode = fsMode;
      isModified = true;
    }
  }
  return;
}

FsCommand Preset::get_fsCommand(uint8_t fsNumber)
{
  if (fsNumber < nbFsConfigs)
  {
    return fsConfigs[fsNumber].fsCommand;
  }
  else
  {
    return 0xFF; //error code
  }
}

void Preset::set_fsCommand(uint8_t fsNumber, FsCommand fsCommand)
{
  if (fsNumber < nbFsConfigs)
  {
    if(fsConfigs[fsNumber].fsCommand != fsCommand)
    {
      fsConfigs[fsNumber].fsCommand = fsCommand;
      isModified = true;
    }
  }
  return;
}

ExpMode Preset::get_expMode(uint8_t expNumber)
{
  if (expNumber < nbExpConfigs)
  {
    return expConfigs[expNumber].expMode;
  }
  else
  {
    return 0xFF; //error code
  }
}

void Preset::set_expMode(uint8_t expNumber, ExpMode expMode)
{
  if (expNumber < nbExpConfigs)
  {
    if (expConfigs[expNumber].expMode != expMode)
    {
      expConfigs[expNumber].expMode = expMode;
      isModified = true;
    }
  }
  return;
}

ExpCommand Preset::get_expCommand(uint8_t expNumber)
{
  if (expNumber < nbExpConfigs)
  {
    return expConfigs[expNumber].expCommand;
  }
  else
  {
    return 0xFF; //error code
  }
}

void Preset::set_expCommand(uint8_t expNumber, ExpCommand expCommand)
{
  if (expNumber < nbExpConfigs)
  {
    if (expConfigs[expNumber].expCommand != expCommand)
    {
      expConfigs[expNumber].expCommand = expCommand;
      isModified = true;
    }
  }
  return;
}
