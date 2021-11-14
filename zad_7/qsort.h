void exch(double v[], int n, int m) {
  double temp = v[n];
  v[n] = v[m];
  v[m] = temp;
}

/* Sort array v in ascending order */
void quicksort(double v[], int l, int r) {
  int i, last;

  if (l >= r) return; // Less than 2 elements
  exch(v, l, (l + r/2));
  last = l;
  for (i = l+1; i<= r; i++)
    if (v[i] < v[l])
      exch(v, ++last, i);
  exch(v, l, last);
  qsort(v, l, last-1);
  qsort(v, last+1, r);
}