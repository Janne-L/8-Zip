// Common/StdOutStream.cpp

#include "StdAfx.h"

#include "StdOutStream.h"
#include "Common/IntToString.h"

static const char kNewLineChar =  '\n';

static LPCTSTR kFileOpenMode = _T("wt");

CStdOutStream  g_StdOut(stdout);
CStdOutStream  g_StdErr(stderr);

bool CStdOutStream::Open(LPCTSTR fileName)
{
  Close();
  _stream = _tfopen(fileName, kFileOpenMode);
  _streamIsOpen = (_stream != 0);
  return _streamIsOpen;
}

bool CStdOutStream::Close()
{
  if(!_streamIsOpen)
    return true;
  _streamIsOpen = (fclose(_stream) != 0);
  return !_streamIsOpen;
}

CStdOutStream::~CStdOutStream ()
{
  Close();
}

CStdOutStream & CStdOutStream::operator<<(CStdOutStream & (*aFunction)(CStdOutStream  &))
{
  (*aFunction)(*this);    
  return *this;
}

CStdOutStream & endl(CStdOutStream & outStream)
{
  return outStream << kNewLineChar;
}

CStdOutStream & CStdOutStream::operator<<(const char *string)
{
  fputs(string, _stream);
  return *this;
}

CStdOutStream & CStdOutStream::operator<<(char c)
{
  fputc(c, _stream);
  return *this;
}

CStdOutStream & CStdOutStream::operator<<(int number)
{
  char textString[16];
  ConvertINT64ToString(number, textString);
  return operator<<(textString);
}

CStdOutStream & CStdOutStream::operator<<(UINT64 number)
{
  char textString[32];
  ConvertUINT64ToString(number, textString);
  return operator<<(textString);
}
