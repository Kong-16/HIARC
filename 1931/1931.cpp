/*
한 회의실에 가장 많은 회의가 들어가는 수 구하기
그리디 알고리즘 사용.
회의가 빨리 끝나는 순서대로 정렬 후 (끝나는 시간이 같다면 시작시간이 빠른 순) 맨 처음 회의 시작.
이후의 회의의 시작시간이 진행 중인 회의 끝 시간보다 늦다면 회의실 사용. 
정렬을 위해 merge sort사용.
*/
#include <iostream>

using namespace std;

struct meeting {
	int start;
	int end;
};

void merge(meeting* initArr, meeting* mergedArr, int l, int m, int n) {//initArr[l:m], initArr[m+1:n]을 정렬해 mergedArr[l:n]에 저장.
	int i1, iResult, i2;
	i1 = iResult = l;
	i2 = m + 1;

	while (i1 <= m && i2 <= n) { //두 배열 비교해 작은 값 부터 순서대로 저장.
		if (initArr[i1].end == initArr[i2].end) { // 끝나는 시간이 같으면 시작 시간이 빠른 순서
			if(initArr[i1].start < initArr[i2].start) mergedArr[iResult++] = initArr[i1++];
			else mergedArr[iResult++] = initArr[i2++];
		}
		else if (initArr[i1].end < initArr[i2].end) mergedArr[iResult++] = initArr[i1++];
		else mergedArr[iResult++] = initArr[i2++];
	}

	copy(initArr + i1, initArr + m + 1, mergedArr + iResult); //m과 n의 길이가 다를 경우 한 쪽이 먼저 끝남. 나머지 값 삽입.
	copy(initArr + i2, initArr + n + 1, mergedArr + iResult);
}

void recursiveMerge(meeting* arr, meeting* tempArr, int left, int right) {//arr[left:right] 재귀합병정렬
	if (left >= right) return;
	int mid = (left + right) / 2; // 배열의 절반
	recursiveMerge(arr, tempArr, left, mid);
	recursiveMerge(arr, tempArr, mid + 1, right); //각 절반을 매개변수로 재귀적 호출 -> 절반씩 쪼개짐
	merge(arr, tempArr, left, mid, right); //다 쪼개질 경우 merge로 합쳐서 tempArr에 저장
	copy(tempArr + left, tempArr + right + 1, arr + left);// 정리된 배열 arr에 다시 넣음. 다음 합병을 위함.
}

void rmergeSort(meeting* arr, int n) {
	meeting* tempArr = new meeting[n + 1];
	recursiveMerge(arr, tempArr, 0, n);
	copy(tempArr, tempArr + n, arr);
}

int main() {
	int num ,start, end, count;

	count = 1;
	cin >> num;

	meeting* meeting_arr = new meeting[num];
	for (int i = 0; i < num; i++) {
		cin >> start >> end;
		meeting_arr[i].start = start;
		meeting_arr[i].end = end;
	}

	rmergeSort(meeting_arr, num - 1);

	end = meeting_arr[0].end;

	for (int i = 1; i < num; i++) {
		if (meeting_arr[i].start >= end) {
			count++;
			end = meeting_arr[i].end;
		}
	}
	cout << count;
}