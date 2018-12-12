import boto3

# Get the device resource
sqs = boto3.resource('sqs')

# Chama um a queue existente
queue = sqs.get_queue_by_name(QueueName='teste')

# Create a new message
response = queue.send_message(MessageBody = 'world')

# A resposta nao e um resource mas da msg ID e MD5
print(response.get('MessageId'))
print(response.get('MD5OfMessageBody'))

# Nova mensagem

print(' ')
print('custom attributes')
print('  ')
queue.send_message(MessageBody='boto3', MessageAttributes={
    'Autor' : {
        'StringValue':'Gustavo',
        'DataType':'String'
    }
})

