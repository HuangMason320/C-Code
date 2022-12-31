int BS(int* arr, int q, int n)
{
	int l=0,r=n,ans=-1;
    while(l<r)
    {
      int m=(l+r)/2;
      if(arr[m]>=q)
      {
        r=m,ans=m;
      }
       else l=m+1;
    }
  return ans;
}