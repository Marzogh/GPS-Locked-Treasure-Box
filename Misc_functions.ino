boolean lidIsOpen(void)
{
  if (lidSensor == LOW) {
    return false;
  }
  else {
    return true;
  }
}

void checkLidState()
{
  if (!lidIsOpen) {
    lock.write(engage);
  }
  else {
    while (1);
  }
}
