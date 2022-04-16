bool checker_ith_element(int *a, int ans, int n, int i)
{
    int below = 0, under = 0;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] <= ans)
        {
            below++;
            if (a[i] ^ ans)
                under++;
        }
    }
    return under < i && below >= i;
}