using WAV

function main()

    if length(ARGS) < 3
        println("Uso: julia delay_audio.jl <input.wav> <delay_ms> <feedback> [output.wav]")
        return
    end

    input_file = ARGS[1]
    delay_ms = parse(Int, ARGS[2])
    feedback = parse(Float64, ARGS[3])
    output_file = length(ARGS) >= 4 ? ARGS[4] : "output_delay.wav"

    x, fs = wavread(input_file)

    N, C = size(x)

    delay_samples = Int(round(fs * delay_ms / 1000))

    buffer = zeros(Float32, delay_samples, C)
    y = zeros(Float32, N, C)

    pos = 1

    for n in 1:N
        for c in 1:C
            delayed = buffer[pos, c]

            y[n, c] = x[n, c] + delayed

            buffer[pos, c] = x[n, c] + feedback * delayed
        end

        pos = mod(pos, delay_samples) + 1
    end

    wavwrite(y, fs, output_file)

    println("Archivo generado: $output_file")

end

main()

