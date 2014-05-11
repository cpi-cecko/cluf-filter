template <int SIZE>
class TemplateArray
{
public:
	int *arr;

	TemplateArray()
	{
		arr = new int[SIZE];
	}
};

int main()
{
	TemplateArray<20> arr;
}