
PLL euk(LL a, LL b)
{
      if(a > b)
      {
            PLL x = euk(b, a);
            return {x.se, x.fi};
      }
      if(a == 0)
            return {0, 1};
      // a <= b
      PLL x = euk(b % a, a);
      return {(x.se - x.fi * (b / a)), x.fi};
}
