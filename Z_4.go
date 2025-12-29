package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	// Ускорение ввода/вывода
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()
	
	// Чтение n и m
	line, _ := reader.ReadString('\n')
	line = strings.TrimSpace(line)
	parts := strings.Split(line, " ")
	n, _ := strconv.Atoi(parts[0])
	m, _ := strconv.Atoi(parts[1])
	
	// Чтение чисел
	line, _ = reader.ReadString('\n')
	line = strings.TrimSpace(line)
	numStrs := strings.Split(line, " ")
	
	// Обработка
	nums := make([]int64, n)
	prefix := make([]int64, n+1)
	
	for i := 0; i < n; i++ {
		nums[i], _ = strconv.ParseInt(numStrs[i], 10, 64)
		prefix[i+1] = prefix[i] + nums[i]
	}
	
	// Динамическое программирование
	dp := make([]int64, n+1)
	
	for i := n - 1; i >= 0; i-- {
		best := int64(-1 << 63)
		limit := m
		if n-i < limit {
			limit = n - i
		}
		
		for k := 1; k <= limit; k++ {
			sum := prefix[i+k] - prefix[i]
			advantage := sum - dp[i+k]
			if advantage > best {
				best = advantage
			}
		}
		
		dp[i] = best
	}
	
	// Вывод результата
	if dp[0] > 0 {
		fmt.Fprintln(writer, 1)
	} else {
		fmt.Fprintln(writer, 0)
	}
}